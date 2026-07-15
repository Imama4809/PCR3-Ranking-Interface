#include <check.h>
#include "trials.h"

START_TEST(test_cut_down_length){
    int n;
    int *neck;
    int *string = NULL;
    int stringLen;
    for (int sizeCutDown = 670;sizeCutDown > 630;sizeCutDown--){ 
        n = 31 - __builtin_clz(sizeCutDown)+1;
        neck = testGetClosestNeckInDBSeqPCR3(sizeCutDown,n);
        if ((1 << n) == sizeCutDown) {
            for (int i=0;i<n;i++) neck[i]=1;
            // printf("%d",1);
            neck[n-1] = 0;
            stringLen = DB(neck,n,&string);
            ck_assert_int_eq(stringLen,sizeCutDown);
            // printString(string,stringLen);
            // printf("\n");
            return;
        } else if ((1 << n) - 1 == sizeCutDown) {
            for (int i=0;i<n;i++) neck[i]=1;
            // printf("%d",1);
            neck[n-1] = 0;
            stringLen = DB(neck,n,&string);
            ck_assert_int_eq(stringLen,sizeCutDown);
            // printString(string,stringLen);
            // printf("\n");
            return;
        } else if ((1 << n) - 2 == sizeCutDown){
            for (int i=0;i<n;i++) neck[i]=1;
            printf("1");
            neck[n-1] = 0;
            stringLen = cutDownDB(neck,(1<<n)-3,n,&string)-1;
            ck_assert_int_eq(stringLen,sizeCutDown);
            // printString(string,stringLen);
            // printf("\n");
            return;
        }
        
        stringLen = cutDownDB(neck,sizeCutDown,n,&string);
        ck_assert_int_eq(stringLen,sizeCutDown);
        // printf("\n");
        // if (sizeCutDown >= (1 <<n) - n) printf("1");
        // printString(string,stringLen);
    }
   
}

START_TEST(testingRankingCutDownDB){
    int n;
    int *neck;
    int *neck2;
    int *string = NULL;
    int stringLen;
    for (int sizeCutDown = 70;sizeCutDown <=80;sizeCutDown++){
        n = 31 - __builtin_clz(sizeCutDown)+1;
        neck = testGetClosestNeckInDBSeqPCR3(sizeCutDown,n);
        neck2 = testGetClosestNeckInDBSeqPCR3(sizeCutDown,n);
        if ((1 << n) == sizeCutDown) {
            for (int i=0;i<n;i++) neck[i]=1;
            neck[n-1] = 0;
            stringLen = DB(neck,n,&string);
        } else if ((1 << n) - 1 == sizeCutDown) {
            for (int i=0;i<n;i++) neck[i]=1;
            neck[n-1] = 0;
            stringLen = DB(neck,n,&string);
        } else if ((1 << n) - 2 == sizeCutDown){
            for (int i=0;i<n;i++) neck[i]=1;
            printf("1");
            neck[n-1] = 0;
            stringLen = cutDownDB(neck,(1<<n)-3,n,&string)-1;
        }
        stringLen = cutDownDB(neck,sizeCutDown,n,&string);

        int* window = malloc(sizeof(int)*n);
        int* copy = malloc(sizeof(int)*n);
        for (int i=0;i<n;i++) window[i] = string[i];
        for (int i =0;i<stringLen;i++){
            for (int j=0;j<n;j++) copy[j] = window[j];
            neck2 = testGetClosestNeckInDBSeqPCR3(sizeCutDown,n);
            int r = rankCutDownDB(neck2,copy,sizeCutDown,n);
            // printf("%d %d %d",n, r, (i+n)%(sizeCutDown));
            // delArrBy1(window,n);
            ck_assert_int_eq(r,sizeCutDown-i);
            for (int j=0;j<n-1;j++){
                window[j] = window[j+1];
            }
            window[n-1] = string[(i+n)%(sizeCutDown)];
        }
    }
}

START_TEST(testingUnrankingCutDownDB){
    int n;
    int *neck;
    int *neck2;
    int *string = NULL;
    int stringLen;
    // int sizeCutDown = 50;
    int *unrankedString = malloc(sizeof(int));
    for (int sizeCutDown = 50;sizeCutDown <=60;sizeCutDown++){
        n = 31 - __builtin_clz(sizeCutDown)+1;
        free(unrankedString);
        unrankedString = malloc(sizeof(int)*n);
        neck = testGetClosestNeckInDBSeqPCR3(sizeCutDown,n);
        neck2 = testGetClosestNeckInDBSeqPCR3(sizeCutDown,n);
        if ((1 << n) == sizeCutDown) {
            for (int i=0;i<n;i++) neck[i]=1;
            neck[n-1] = 0;
            stringLen = DB(neck,n,&string);
            return;
        } else if ((1 << n) - 1 == sizeCutDown) {
            for (int i=0;i<n;i++) neck[i]=1;
            neck[n-1] = 0;
            stringLen = DB(neck,n,&string);
            return;
        } else if ((1 << n) - 2 == sizeCutDown){
            for (int i=0;i<n;i++) neck[i]=1;
            printf("1");
            neck[n-1] = 0;
            stringLen = cutDownDB(neck,(1<<n)-3,n,&string)-1;
        }
        stringLen = cutDownDB(neck,sizeCutDown,n,&string);



        int* window = malloc(sizeof(int)*n);
        int* copy = malloc(sizeof(int)*n);
        for (int i=0;i<n;i++) window[i] = string[i];
        for (int i =0;i<stringLen;i++){
            for (int j=0;j<n;j++) copy[j] = window[j];
            // for (int j=0;j<n;j++) printf("%d",copy[j]);
            neck2 = testGetClosestNeckInDBSeqPCR3(sizeCutDown,n);
            unrankCutDownDB(neck2,sizeCutDown - i,sizeCutDown,n,unrankedString);
            // // printf("%d %d %d",n, r, (i+n)%(sizeCutDown));
            // // printf("\n");
            // // delArrBy1(window,n);
            // printf("position:%d\n",sizeCutDown - i);
            // for (int i =0;i<n;i++) printf("%d",unrankedString[i]);
            // printf("\n");
            // for (int i =0;i<n;i++) printf("%d",copy[i]);
            // printf("\n");
            // printf("\n");
            ck_assert_int_eq(areArraysEqual(copy,unrankedString,n),1);
            for (int j=0;j<n-1;j++){
                window[j] = window[j+1];
            }
            window[n-1] = string[(i+n)%(sizeCutDown)];
        }
    }
}


START_TEST(testingUnrankingCutDownDB100110){
    int n;
    int *neck;
    int *neck2;
    int *string = NULL;
    int stringLen;
    // int sizeCutDown = 50;
    int *unrankedString = malloc(sizeof(int));
    for (int sizeCutDown = 100;sizeCutDown <=110;sizeCutDown++){
        n = 31 - __builtin_clz(sizeCutDown)+1;
        free(unrankedString);
        unrankedString = malloc(sizeof(int)*n);
        neck = testGetClosestNeckInDBSeqPCR3(sizeCutDown,n);
        neck2 = testGetClosestNeckInDBSeqPCR3(sizeCutDown,n);
        if ((1 << n) == sizeCutDown) {
            for (int i=0;i<n;i++) neck[i]=1;
            neck[n-1] = 0;
            stringLen = DB(neck,n,&string);
            return;
        } else if ((1 << n) - 1 == sizeCutDown) {
            for (int i=0;i<n;i++) neck[i]=1;
            neck[n-1] = 0;
            stringLen = DB(neck,n,&string);
            return;
        } else if ((1 << n) - 2 == sizeCutDown){
            for (int i=0;i<n;i++) neck[i]=1;
            printf("1");
            neck[n-1] = 0;
            stringLen = cutDownDB(neck,(1<<n)-3,n,&string)-1;
        }
        stringLen = cutDownDB(neck,sizeCutDown,n,&string);



        int* window = malloc(sizeof(int)*n);
        int* copy = malloc(sizeof(int)*n);
        for (int i=0;i<n;i++) window[i] = string[i];
        for (int i =0;i<stringLen;i++){
            for (int j=0;j<n;j++) copy[j] = window[j];
            // for (int j=0;j<n;j++) printf("%d",copy[j]);
            neck2 = testGetClosestNeckInDBSeqPCR3(sizeCutDown,n);
            unrankCutDownDB(neck2,sizeCutDown - i,sizeCutDown,n,unrankedString);
            // // printf("%d %d %d",n, r, (i+n)%(sizeCutDown));
            // // printf("\n");
            // // delArrBy1(window,n);
            // printf("position:%d\n",sizeCutDown - i);
            // printf("size: %d\n",sizeCutDown);
            // for (int i =0;i<n;i++) printf("%d",unrankedString[i]);
            // printf("\n");
            // for (int i =0;i<n;i++) printf("%d",copy[i]);
            // printf("\n");
            // printf("\n");
            ck_assert_int_eq(areArraysEqual(copy,unrankedString,n),1);
            for (int j=0;j<n-1;j++){
                window[j] = window[j+1];
            }
            window[n-1] = string[(i+n)%(sizeCutDown)];
        }
    }
}

START_TEST(testingUnrankingCutDownDB275280){
    int n;
    int *neck;
    int *neck2;
    int *string = NULL;
    int stringLen;
    // int sizeCutDown = 50;
    int *unrankedString = malloc(sizeof(int));
    for (int sizeCutDown = 275;sizeCutDown <=275;sizeCutDown++){
        n = 31 - __builtin_clz(sizeCutDown)+1;
        free(unrankedString);
        unrankedString = malloc(sizeof(int)*n);
        neck = testGetClosestNeckInDBSeqPCR3(sizeCutDown,n);
        neck2 = testGetClosestNeckInDBSeqPCR3(sizeCutDown,n);
        if ((1 << n) == sizeCutDown) {
            for (int i=0;i<n;i++) neck[i]=1;
            neck[n-1] = 0;
            stringLen = DB(neck,n,&string);
            return;
        } else if ((1 << n) - 1 == sizeCutDown) {
            for (int i=0;i<n;i++) neck[i]=1;
            neck[n-1] = 0;
            stringLen = DB(neck,n,&string);
            return;
        } else if ((1 << n) - 2 == sizeCutDown){
            for (int i=0;i<n;i++) neck[i]=1;
            printf("1");
            neck[n-1] = 0;
            stringLen = cutDownDB(neck,(1<<n)-3,n,&string)-1;
        }
        stringLen = cutDownDB(neck,sizeCutDown,n,&string);



        int* window = malloc(sizeof(int)*n);
        int* copy = malloc(sizeof(int)*n);
        for (int i=0;i<n;i++) window[i] = string[i];
        for (int i =0;i<stringLen;i++){
            for (int j=0;j<n;j++) copy[j] = window[j];
            // for (int j=0;j<n;j++) printf("%d",copy[j]);
            neck2 = testGetClosestNeckInDBSeqPCR3(sizeCutDown,n);
            unrankCutDownDB(neck2,sizeCutDown - i,sizeCutDown,n,unrankedString);
            // // printf("%d %d %d",n, r, (i+n)%(sizeCutDown));
            // // printf("\n");
            // // delArrBy1(window,n);
            // printf("position:%d\n",sizeCutDown - i);
            // printf("size: %d\n",sizeCutDown);
            // for (int i =0;i<n;i++) printf("%d",unrankedString[i]);
            // printf("\n");
            // for (int i =0;i<n;i++) printf("%d",copy[i]);
            // printf("\n");
            // printf("\n");
            ck_assert_int_eq(areArraysEqual(copy,unrankedString,n),1);
            for (int j=0;j<n-1;j++){
                window[j] = window[j+1];
            }
            window[n-1] = string[(i+n)%(sizeCutDown)];
        }
    }
}




Suite *PCR3_Cut_Suite(void){
    Suite *s = suite_create("PCR3_Cut_Suite");
    TCase *tc_core = tcase_create("Core_Tests");

    tcase_add_test(tc_core,test_cut_down_length);
    tcase_add_test(tc_core,testingRankingCutDownDB);
    tcase_add_test(tc_core,testingUnrankingCutDownDB);
    tcase_add_test(tc_core,testingUnrankingCutDownDB100110);
    tcase_add_test(tc_core,testingUnrankingCutDownDB275280);

    suite_add_tcase(s,tc_core);
    return s;
}