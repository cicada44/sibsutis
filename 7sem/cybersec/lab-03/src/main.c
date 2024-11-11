#include "../include/extralib.h"
#include "../include/colorlib.h"

int main(int argc, const char *argv[])
{
    char rsa[] = "./test.jpg";
    RSA_sign(rsa);
    rsa[10] = '\0';
    if (RSA_sign_check(rsa)) {
        printf("%sRSA%s %ssignature result:%s\t%s[FAILED]%s\n", YELLOW, RESET, WHITE, RESET, RED, RESET);
    } else {
        printf("%sRSA%s %ssignature result:%s\t%s[SUCCESS]%s\n", YELLOW, RESET, WHITE, RESET, GREEN, RESET);
    }

    char elg[] = "./test.jpg";
    ELG_sign(elg);
    elg[10] = '\0';
    if (ELG_sign_check(elg)) {
        printf("%sELG%s %ssignature result:%s\t%s[FAILED]%s\n", YELLOW, RESET, WHITE, RESET, RED, RESET);
    } else {
        printf("%sELG%s %ssignature result:%s\t%s[SUCCESS]%s\n", YELLOW, RESET, WHITE, RESET, GREEN, RESET);
    }

    char gost[256] = "./test.jpg";
    GOST_sign(gost);
    gost[10] = '\0';
    if (GOST_sign_check(gost)) {
        printf("%sGOST%s %ssignature result:%s\t%s[FAILED]%s\n", YELLOW, RESET, WHITE, RESET, RED, RESET);
    } else {
        printf("%sGOST%s %ssignature result:%s\t%s[SUCCESS]%s\n", YELLOW, RESET, WHITE, RESET, GREEN, RESET);
    }

    return 0;
}
