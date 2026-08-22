#include <check.h>
#include "../inc/trials.h"

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
    for (int sizeCutDown = 70;sizeCutDown <=75;sizeCutDown++){
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
            fflush(stdout);
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
    for (int sizeCutDown = 50;sizeCutDown <=55;sizeCutDown++){
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
    // printf("hello");
    fflush(stdout);
    for (int sizeCutDown = 100;sizeCutDown <=105;sizeCutDown++){
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
            // printf("%d %d %d",n, r, (i+n)%(sizeCutDown));
            // printf("\n");
            // delArrBy1(window,n);
            printf("position:%d\n",sizeCutDown - i);
            printf("size: %d\n",sizeCutDown);
            for (int i =0;i<n;i++) printf("%d",unrankedString[i]);
            printf("\n");
            for (int i =0;i<n;i++) printf("%d",copy[i]);
            printf("\n");
            printf("\n");
    fflush(stdout);

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
            unrankCutDownDB(neck2,sizeCutDown,sizeCutDown,n,unrankedString);
            // printf("%d %d %d",n, r, (i+n)%(sizeCutDown));
            // printf("\n");
            // delArrBy1(window,n);
            printf("position:%d\n",sizeCutDown - i);
            printf("size: %d\n",sizeCutDown);
            for (int i =0;i<n;i++) printf("%d",unrankedString[i]);
            printf("\n");
            for (int i =0;i<n;i++) printf("%d",copy[i]);
            printf("\n");
            printf("\n");
            ck_assert_int_eq(areArraysEqual(copy,unrankedString,n),1);
            for (int j=0;j<n-1;j++){
                window[j] = window[j+1];
            }
            window[n-1] = string[(i+n)%(sizeCutDown)];
        }
    }
}

START_TEST(testGetClosestNeckInDBSeqPCR3test){
    int n = 10;
    int *alpha = malloc(sizeof(int)*n);
    int *closestNeckActual = malloc(sizeof(int)*n);
    int *closestNeckFunc = malloc(sizeof(int)*n);
    for (int i =0;i<n;i++) alpha[i] = 1;
    alpha[n-1] = 0;
    int dbLen;
    int *string = NULL;
    dbLen = DB(alpha,n,&string);
    for (int i =0;i<n;i++) alpha[i] = string[i];
    for (int i=0;i<n;i++) closestNeckActual[i] = alpha[i];
    getClosestNeckInDBSeq(0,n,closestNeckFunc);
    for (int i =0;i<n;i++) printf("%d",closestNeckFunc[i]);
        printf(" \n");
    // ck_assert_int_eq(1, areArraysEqual(closestNeckActual,closestNeckFunc,n));
    for (int i =0;i<dbLen-n;i++){
        printf("Len of seq from here: %d\n",i+1);
        for (int i =0;i<n-1;i++) alpha[i] = alpha[i+1];
        alpha[n-1] = string[i+n];
        if (isNecklacePCR3(alpha,n)){
            for (int i=0;i<n;i++) closestNeckActual[i] = alpha[i];
        }
        for (int i =0;i<n;i++) printf("%d",alpha[i]);
        printf(" \n");
        getClosestNeckInDBSeq(i+1,n,closestNeckFunc);
        printf("Closest Neck: ");
        for (int i =0;i<n;i++) printf("%d",closestNeckFunc[i]);
        printf(" \n");
        // ck_assert_int_eq(1, areArraysEqual(closestNeckActual,closestNeckFunc,n));
    }     
    free(alpha);
    free(closestNeckActual);
    free(closestNeckFunc);
}

START_TEST(testingNewCutDownGenFunction){
    int len;
    int *str = NULL;
    // len= newCutDownDB(70,&str);
    for (int i =10;i<=200;i++){
        len = newCutDownDB(i,&str);
        ck_assert_int_eq(len,i);
        if (i != len){
            for (int j=0;j<len;j++){
                printf("%d",str[j]);
            }
            printf("\n");
            printf("%d %d", i, len);
            // break;
        }
        free(str);
    }
}

START_TEST(testingNewCutDownRankFunction){
    int len;
    int *str = NULL;
    int size = 2000;
    int n = (size == 0) ? 1 : 32 - __builtin_clz(size);
    int guessRank;
    int *window = malloc(sizeof(int)*n);
    for (size = 1995;size<1996;size++){
        len = newCutDownDB(size,&str);
        for (int i =0;i<n;i++) window[i] = str[i];
        for (int i =0;i<len;i++) printf("%d",str[i]);
        printf("\n");
        for (int i =n;i<len;i++){
            for (int j=0;j<n-1;j++) window[j] = window[j+1];
            window[n-1] = str[i];
            guessRank = newRankCutDownDB(window,size);
            for (int j=0;j<n;j++) printf("%d",window[j]);
            printf(" %d %d\n",i-n+1,guessRank);
            ck_assert_int_eq(i-n+1,guessRank);
        }
    }
}

START_TEST(testingNewCutDownUnrankFunction){
    int len;
    int *str = NULL;
    int size = 1995;
    int n = (size == 0) ? 1 : 32 - __builtin_clz(size);
    int guessRank;
    int *window = malloc(sizeof(int)*n);
    int *rbpstr = malloc(sizeof(int)*n);
    for (size = 1995;size<=2005;size++){
        len = newCutDownDB(size,&str);
        for (int i =0;i<n;i++) window[i] = str[i];
        for (int i =0;i<len;i++) printf("%d",str[i]);
        printf("\n");
        for (int i =n;i<len;i++){
            for (int j=0;j<n-1;j++) window[j] = window[j+1];
            window[n-1] = str[i];
            guessRank = newRankCutDownDB(window,size);
            for (int j=0;j<n;j++) printf("%d",window[j]);            
            newUnrankCutDownDB(guessRank,size,rbpstr);
            for (int j=0;j<n;j++) printf("%d",rbpstr[j]);
            printf(" %d %d\n",i-n+1,guessRank);
            ck_assert_int_eq(areArraysEqual(rbpstr,window,n),1);
        }
    }
}

START_TEST(thingy){
    int *str = malloc(sizeof(int));
    int *str1 = malloc(sizeof(int));
    for (int n=10;n<100;n++){
        str = realloc(str,sizeof(int)*n);
        str1 = realloc(str1,sizeof(int)*n);
        str[0] =1;
        for (int i = 1;i<n;i++) str[i] = 0;
        int r = getRank(str,n);
        unrank(r,n,str1);
        printf("%d",n);
        for (int j =0;j<n;j++) printf("%d",str[j]);
        printf(" ");
        for (int j =0;j<n;j++) printf("%d",str1[j]);
        printf(" \n");
        fflush(stdout);
        ck_assert_int_eq(1,areArraysEqual(str,str1,n));
    }
}


Suite *PCR3_Cut_Suite(void){
    Suite *s = suite_create("PCR3_Cut_Suite");
    TCase *tc_core = tcase_create("Core_Tests");
    tcase_set_timeout(tc_core, 400);
    // tcase_add_test(tc_core,test_cut_down_length);
    // tcase_add_test(tc_core,testingRankingCutDownDB);
    // tcase_add_test(tc_core,testingUnrankingCutDownDB);
    // tcase_add_test(tc_core,testingUnrankingCutDownDB100110);
    // tcase_add_test(tc_core,testingUnrankingCutDownDB275280);
    // tcase_add_test(tc_core,testGetClosestNeckInDBSeqPCR3test);
    // tcase_add_test(tc_core,testingNewCutDownGenFunction);
    // tcase_add_test(tc_core,testingNewCutDownRankFunction);
    tcase_add_test(tc_core,testingNewCutDownUnrankFunction);
    // tcase_add_test(tc_core,thingy);

    suite_add_tcase(s,tc_core);
    return s;
}