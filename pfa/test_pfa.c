/******************************************************/
/* Program to run and test the integration functions. */
/* Creation date: 31 July, 2025                       */
/******************************************************/

#include <stdio.h>
#include <string.h>
#include "pfa.h"
#include "integration.h"

int main()
{
    if (!init_integration("gauss3", 0.05)) {
        printf("Erreur d'initialisation.\n");
        return 1;
    }

    printf("=== FINANCE ===\n");
    Option opt;
    opt.type = CALL;
    opt.S0 = 100.0;
    opt.K = 105.0;
    opt.T = 1.0;
    opt.mu = 0.05;
    opt.sig = 0.2;

    double prix_call = optionPrice(&opt);
    printf("Prix du Call : %f\n", prix_call);

    opt.type = PUT;
    double prix_put = optionPrice(&opt);
    printf("Prix du Put  : %f\n\n", prix_put);

    printf("=== ASSURANCE ===\n");
    InsuredClient client;
    client.m = 1.5;
    client.s = 0.4;
    client.p[0] = 0.7;
    client.p[1] = 0.2;
    client.p[2] = 0.1;

    double x = 10.0;
    double resultat_s = clientCDF_S(&client, x);
    printf("CDF_S pour x=%f : %f\n", x, resultat_s);

    return 0;
}
