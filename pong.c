/*
** EPITECH PROJECT, 2025
** 101pong
** File description:
** 101pong
*/

#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "pong.h"

static vector_t *vec1(double x0, double y0, double z0)
{
    vector_t *vect1 = malloc(sizeof(vector_t));

    vect1->x = x0;
    vect1->y = y0;
    vect1->z = z0;
    return vect1;
}

static vector_t *vec2(double x1, double y1, double z1)
{
    vector_t *vect2 = malloc(sizeof(vector_t));

    vect2->x = x1;
    vect2->y = y1;
    vect2->z = z1;
    return vect2;
}

static vector_t velocity(vector_t *vect1, vector_t *vect2)
{
    vector_t vel;

    vel.x = vect2->x - vect1->x;
    vel.y = vect2->y - vect1->y;
    vel.z = vect2->z - vect1->z;
    return vel;
}

vector_t position_final(vector_t *vect2, vector_t vel, int n)
{
    vector_t pos;

    pos.x = vect2->x + vel.x * n;
    pos.y = vect2->y + vel.y * n;
    pos.z = vect2->z + vel.z * n;
    return pos;
}

void print_help(void)
{
    printf("USAGE\n");
    printf("    ./101pong x0 y0 z0 x1 y1 z1 n\n\n");
    printf("DESCRIPTION\n");
    printf("    x0 ball abscissa at time t - 1\n");
    printf("    y0 ball ordinate at time t - 1\n");
    printf("    z0 ball altitude at time t - 1\n");
    printf("    x1 ball abscissa at time t\n");
    printf("    y1 ball ordinate at time t\n");
    printf("    z1 ball altitude at time t\n");
    printf("    n  time shift (greater than or equal to zero, integer)\n");
}

static int is_valid_number(char *str)
{
    int i = 0;
    int has_dot = 0;
    
    if (str == NULL || str[0] == '\0')
        return 0;
    if (str[0] == '-' || str[0] == '+')
        i++;
    if (str[i] == '\0')
        return 0;
    while (str[i] != '\0') {
        if (str[i] == '.') {
            if (has_dot)
                return 0;
            has_dot = 1;
        } else if (str[i] < '0' || str[i] > '9') {
            return 0;
        }
        i++;
    }
    return 1;
}

static int is_valid_integer(char *str)
{
    int i = 0;
    
    if (str == NULL || str[0] == '\0')
        return 0;
    if (str[0] == '-' || str[0] == '+')
        i++;
    if (str[i] == '\0')
        return 0;
    while (str[i] != '\0') {
        if (str[i] == '.' || str[i] < '0' || str[i] > '9')
            return 0;
        i++;
    }
    return 1;
}

static int check_args(int ac, char **av)
{
    if (ac == 2 && strcmp(av[1], "-h") == 0) {
        print_help();
        return 1;
    }
    if (ac != 8) {
        return 84;
    }
    for (int i = 1; i <= 6; i++) {
        if (!is_valid_number(av[i])) {
            return 84;
        }
    }
    if (!is_valid_integer(av[7])) {
        return 84;
    }
    int n = atoi(av[7]);
    if (n < 0) {
        return 84;
    }
    
    return 0;
}

static int angle(vector_t vel, double z)
{
    double norm;
    double angle;

    norm = sqrt(pow(vel.x, 2.00) + pow(vel.y, 2.00) + pow(vel.z, 2.00));
    if (norm == 0)
        return 84;
    else {
        angle = fabs(asin(vel.z / norm) * (180 / M_PI));
        printf("The incidence angle is:\n%.2f degrees\n", angle);
    }
    return 0;
}

int main(int ac, char **av)
{
    vector_t *vector1;
    vector_t *vector2;
    vector_t vel;
    vector_t pos;
    vector_t verif;
    int check = check_args(ac, av);

    if (check == 1)
        return 0;
    if (check == 84)
        return 84;
    
    double x0 = atof(av[1]);
    double y0 = atof(av[2]);
    double z0 = atof(av[3]);
    double x1 = atof(av[4]);
    double y1 = atof(av[5]);
    double z1 = atof(av[6]);
    int n = atoi(av[7]);
    vector1 = vec1(x0, y0, z0);
    vector2 = vec2(x1, y1, z1);
    vel = velocity(vector1, vector2);
    pos = position_final(vector2, vel, n);
    verif.z = vector2->z * pos.z;
    printf("The velocity vector of the ball is:\n(%.2f, %.2f, %.2f)\n", vel.x, vel.y, vel.z);
    printf("At time t + %d, ball coordinates will be:\n(%.2f, %.2f, %.2f)\n", n, pos.x, pos.y, pos.z);
    if (verif.z > 0)
        printf("The ball won't reach the paddle.\n");
    else
        angle(vel, vel.z);
    free(vector1);
    free(vector2);
    return 0;
}
