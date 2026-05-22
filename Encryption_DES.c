
#include <stdio.h>
#include <string.h>

int E[48] = {
    7,7,23,8,24,30, 23,6,22,9,25,14,
    8,5,21,10,26,17, 24,4,20,11,27,1,
    0,3,19,12,28,25, 16,2,18,13,29,9,
    15,1,17,14,30,22, 31,0,16,15,31,6
};

int P[32] = {
    8,7,24,23, 9,6,25,22,
    10,5,26,21, 11,4,27,20,
    12,3,28,19, 13,2,29,18,
    14,1,30,17, 15,0,31,16
};

int PC2[48] = {
    31,0,16,15,31,6,
    15,1,17,14,30,22,
    16,2,18,13,29,9,
    0,3,19,12,28,25,
    24,4,20,11,27,1,
    8,5,21,10,26,17,
    23,6,22,9,25,14,
    7,7,23,8,24,30
};

int S[8][4][16] = {
{
{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
{0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
{4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
{15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}
},
{
{15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
{3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
{0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
{13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}
},
{
{10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
{13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
{13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
{1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}
},
{
{7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
{13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
{10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
{3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}
},
{
{2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
{14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
{4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
{11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}
},
{
{12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
{10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
{9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
{4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}
},
{
{4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
{13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
{1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
{6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}
},
{
{13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
{1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
{7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
{2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}
}
};

void permute(char input[], int table[], int size, char output[]) {
    int i;
    for (i = 0; i < size; i++) {
        output[i] = input[table[i]];
    }
    output[size] = '\0';
}

void xorOperation(char a[], char b[], char result[]) {
    int i;
    for (i = 0; a[i] != '\0'; i++) {
        result[i] = (a[i] == b[i]) ? '0' : '1';
    }
    result[i] = '\0';
}

void leftShift(char input[], int shift, char output[]) {
    int len = strlen(input);
    int i;

    for (i = 0; i < len; i++) {
        output[i] = input[(i + shift) % len];
    }

    output[len] = '\0';
}

void decimalToBinary4(int n, char output[]) {
    output[0] = ((n & 8) ? '1' : '0');
    output[1] = ((n & 4) ? '1' : '0');
    output[2] = ((n & 2) ? '1' : '0');
    output[3] = ((n & 1) ? '1' : '0');
    output[4] = '\0';
}

void sBoxSubstitution(char input48[], char output32[]) {
    int i;
    char block[7];
    char bin4[5];
    output32[0] = '\0';

    for (i = 0; i < 8; i++) {
        strncpy(block, input48 + i * 6, 6);
        block[6] = '\0';

        int row = (block[0] - '0') * 2 + (block[5] - '0');
        int col = (block[1] - '0') * 8 +
                  (block[2] - '0') * 4 +
                  (block[3] - '0') * 2 +
                  (block[4] - '0');

        int value = S[i][row][col];

        decimalToBinary4(value, bin4);
        strcat(output32, bin4);
    }
}

int main() {
    char input64[65], key56[57];

    char L0[33], R0[33];
    char C0[29], D0[29];
    char C1[29], D1[29];
    char combinedKey[57], K1[49];

    char expandedR0[49];
    char xorResult[49];
    char sBoxOutput[33];
    char fOutput[33];

    char L1[33], R1[33];
    char round1Output[65];

    printf("Enter 64-bit input after Initial Permutation: ");
    scanf("%64s", input64);

    printf("Enter 56-bit key after PC-1: ");
    scanf("%56s", key56);

    if (strlen(input64) != 64 || strlen(key56) != 56) {
        printf("Invalid input length!\n");
        return 0;
    }

    strncpy(L0, input64, 32);
    L0[32] = '\0';

    strncpy(R0, input64 + 32, 32);
    R0[32] = '\0';

    strncpy(C0, key56, 28);
    C0[28] = '\0';

    strncpy(D0, key56 + 28, 28);
    D0[28] = '\0';

    leftShift(C0, 1, C1);
    leftShift(D0, 1, D1);

    strcpy(combinedKey, C1);
    strcat(combinedKey, D1);

    permute(combinedKey, PC2, 48, K1);

    permute(R0, E, 48, expandedR0);

    xorOperation(expandedR0, K1, xorResult);

    sBoxSubstitution(xorResult, sBoxOutput);

    permute(sBoxOutput, P, 32, fOutput);

    strcpy(L1, R0);
    xorOperation(L0, fOutput, R1);

    strcpy(round1Output, L1);
    strcat(round1Output, R1);

    printf("\nL0: %s", L0);
    printf("\nR0: %s", R0);

    printf("\n\nC1: %s", C1);
    printf("\nD1: %s", D1);
    printf("\nSubkey K1: %s", K1);

    printf("\n\nExpanded R0: %s", expandedR0);
    printf("\nAfter XOR with K1: %s", xorResult);
    printf("\nAfter S-Box: %s", sBoxOutput);
    printf("\nAfter P Permutation: %s", fOutput);

    printf("\n\nL1: %s", L1);
    printf("\nR1: %s", R1);

    printf("\n\nFinal Output of DES Round 1: %s\n", round1Output);

    return 0;
}
