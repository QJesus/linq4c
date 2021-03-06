#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gc.h>

#include "ArrayList.h"
#include "linq.h"

#define LINQ_PTR lq

struct ProductInfo {
    char Owner[32];
    char Name[32];
};

struct joinOwner{
    char Name[64];
};

struct joinPets {
    char Name[64];
    int Age;
    struct joinOwner *Owner;
};

struct GroupJoin_KeyValue {
    void *Key;   
    void *Value;
};

struct dummyStruct {
    char *str;
    int val;
};

ArrayList testWithNormal(ArrayList array) {
    Linq *lq = From(array);

    ArrayList result = 
        lq
        ->WHERE(lambda(bool, (void *item) {
            char *str= (char *)item;
            return str[0] == 'h';
        }))
        ->SELECT(lambda(void *, (void *item) {
            return newStr("%s_1", (char *)item);
        }))
        ->TO_ARRAY();
    return result;
}

ArrayList testWithNormal2() {
    Linq *lq = Range(3, 2);

    int *a1 = newInt(5);
    int *a2 = newInt(2);
    int *a3 = newInt(1);

    ArrayList result =
        lq
        ->APPEND(a1)
        ->PREPEND(a2)
        ->PREPEND(a3)
        ->TO_ARRAY();
    return result;
}

ArrayList testWithUnion(ArrayList array, Linq *otherLq) {
    Linq *lq = From(array);
    ArrayList result = 
        lq
        ->UNION(otherLq, lambda(bool, (void *item1, void *item2) {
            char *str1= (char *)item1;
            char *str2= (char *)item2;
            return strcmp(str1, str2) == 0;
        }))
        ->TO_ARRAY();

    return result;
}

ArrayList testWithIntersect(ArrayList array, Linq *otherLq) {
    Linq *lq = From(array);
    ArrayList result = 
        lq
        ->INTERSECT(otherLq, lambda(bool, (void *item1, void *item2) {
            char *str1= (char *)item1;
            char *str2= (char *)item2;
            return strcmp(str1, str2) == 0;
        }))
        ->TO_ARRAY();

    return result;
}

long long testWithSumInts(ArrayList array) {
    Linq *lq = From(array);
    int result = lq->SUM_INTS();

    return result;
}

double testWithSumFloats(ArrayList array) {
    Linq *lq = From(array);
    float result = lq->SUM_FLOATS();

    return result;
}

int testWithMaxInts(ArrayList array) {
    Linq *lq = From(array);
    int result = lq->MAX_INTS();

    return result;
}

float testWithMaxFloats(ArrayList array) {
    Linq *lq = From(array);
    float result = lq->MAX_FLOATS();

    return result;
}

int testWithMinInts(ArrayList array) {
    Linq *lq = From(array);
    int result = lq->MIN_INTS();

    return result;
}

float testWithMinFloats(ArrayList array) {
    Linq *lq = From(array);
    float result = lq->MIN_FLOATS();

    return result;
}

float testWithAverageInts(ArrayList array) {
    Linq *lq = From(array);
    float result = lq->AVERAGE_INTS();

    return result;
}

float testWithAverageFloats(ArrayList array) {
    Linq *lq = From(array);
    float result = lq->AVERAGE_FLOATS();

    return result;
}

void *testWithMax(ArrayList array) {
    Linq *lq = From(array);
    void *result =
        lq
        ->MAX(lambda(int, (void *item1, void *item2) {
            int a = TOINT(item1);
            int b = TOINT(item2);
            COMPARE_NUM(a, b);
        }));

    return result;
}

void *testWithMin(ArrayList array) {
    Linq *lq = From(array);
    void *result =
        lq
        ->MIN(lambda(int, (void *item1, void *item2) {
            double a = atof((char *)item1);
            double b = atof((char *)item2);
            COMPARE_NUM(a, b);
        }));

    return result;
}

ArrayList testWithPrepend(ArrayList array) {
    Linq *lq = From(array);

    char *str = newStr("10000000");

    ArrayList result = 
        lq
        ->PREPEND(str)
        ->TO_ARRAY();

    return result;
}

ArrayList testWithAppend(ArrayList array) {
    Linq *lq = From(array);

    char *str = newStr("10000000");
    ArrayList result = 
        lq
        ->APPEND(str)
        ->TO_ARRAY();

    return result;
}

ArrayList testWithSort1(ArrayList array) {
    Linq *lq = From(array);
    ArrayList result = 
        lq
        ->ORDERBY(lambda(int, (void *a, void *b) {
            char *str1= (char *)a;
            char *str2= (char *)b;
            return strcmp(str1, str2);
        }))
        ->TO_ARRAY();

    return result;
}

ArrayList testWithSort2(ArrayList array) {
    Linq *lq = From(array);
    ArrayList result = 
        lq
        ->ORDERBY(lambda(int, (void *a, void *b) {
            double f1= atof((char *)a);
            double f2= atof((char *)b);
            COMPARE_NUM(f1, f2);
        }))
        ->TO_ARRAY();

    return result;
}

ArrayList testWithSortDesc1(ArrayList array) {
    Linq *lq = From(array);
    ArrayList result = 
        lq
        ->ORDERBY_DESC(lambda(int, (void *a, void *b) {
            char *str1= (char *)a;
            char *str2= (char *)b;
            return strcmp(str1, str2);
        }))
        ->TO_ARRAY();

    return result;
}
ArrayList testWithSortDesc2(ArrayList array) {
    Linq *lq = From(array);
    ArrayList result = 
        lq
        ->ORDERBY_DESC(
                      lambda(int, (void *a, void *b) {
                          double f1= atof((char *)a);
                          double f2= atof((char *)b);
                          COMPARE_NUM(f1, f2); }))
        ->TO_ARRAY();

    return result;
}

ArrayList testWithGroupBy(ArrayList array) {
    Linq *lq = From(array);

    ArrayList result = 
        lq
        ->GROUPBY(
                  lambda(void *, (void *item) {
                      struct ProductInfo *pi = (struct ProductInfo *)item;
                      return pi->Owner; }), 
                  lambda(bool, (void *a, void *b) {
                      char *ownerA = (char *)a;
                      char *ownerB = (char *)b;
                      return strcmp(ownerA, ownerB) == 0; }),
                  lambda(void *, (void *item) {
                      struct ProductInfo *pi = (struct ProductInfo *)item;
                      return pi->Name; }))
        ->TO_ARRAY();

    return result;
}

ArrayList testWithGroupBy2(ArrayList array) {
    Linq *lq = From(array);
    ArrayList result = 
        lq
        ->GROUPBY(
                  lambda(void *, (void *item) {
                      int i = TOINT(item);
                      char *result = GC_malloc(8);
                      if ( i % 2 == 0) {
                          strcpy(result, "even");
                          return result;
                      }
                      strcpy(result, "odd");
                      return result; }), 
                  lambda(bool, (void *a, void *b) {
                      int ia = TOINT(a);
                      int ib = TOINT(b);
                      return ia == ib; }),
                  lambda(void *, (void *item) {
                      return item; }))
        ->TO_ARRAY();

    return result;
}

char *testWithJoinStr(ArrayList str_array) {
    Linq *lq = From(str_array);
    char *result = lq->JOIN_STR("---");
    return result;
}

ArrayList testWithJoin(Linq *innerLinq, ArrayList joinOwnerArr, ArrayList joinPetsArr) {
    Linq *lq = From(joinOwnerArr);
    ArrayList result = 
        lq
        ->JOIN(
               innerLinq,
               lambda(bool, (void *a, void *b) {
                   char *stra = (char *)a;
                   char *strb = (char *)b;
                   return strcmp(stra, strb) == 0; }),
               lambda(void *, (void *item) {
                   struct joinOwner *owner = (struct joinOwner *)item;
                   return owner->Name; }),
               lambda(void *, (void *item) {
                   struct joinPets *pets = (struct joinPets *)item;
                   return pets->Owner->Name; }),
               lambda(void *, (void *item1, void *item2) {
                   struct joinOwner *owner = (struct joinOwner *)item1;
                   struct joinPets  *pets = (struct joinPets *)item2;

                   char *result = GC_malloc(128);
                   sprintf(result, "{%s - %s}", owner->Name, pets->Name);
                   return result; }))
        ->TO_ARRAY();

    return result;
}

ArrayList testWithGroupJoin(Linq *innerLinq, ArrayList outerArr) {
    Linq *lq = From(outerArr);
    ArrayList result = 
        lq
        ->GROUP_JOIN( 
                    innerLinq,
                    lambda(bool, (void *a, void *b) {
                        int ia = TOINT(a);
                        int ib = TOINT(b);
                        return ia == ib; }),
                    lambda(void *, (void *item) {
                        return item; }),
                    lambda(void *, (void *item) {
                        int x = TOINT(item);
                        int *result = newInt(x % 2);
                        return result;}),
                    lambda(void *, (void *outerItem, void *innerArray) {
                        int *len = GC_malloc(sizeof(int));
                        *len = arrlist_size((ArrayList)innerArray);
                        struct GroupJoin_KeyValue *kv = GC_malloc(sizeof(struct GroupJoin_KeyValue));
                        kv->Key = outerItem;
                        kv->Value = len;
                        return kv; }))
        ->TO_ARRAY();
    return result;
}

void *testWithAggregate(ArrayList arr) {
    Linq *lq = From(arr);
    void *result = 
        lq
        ->AGGREGATE(
                    lambda(void *, (void *item1, void *item2) {
                        char *str1 = (char *)item1;
                        char *str2 = (char *)item2;
                        if (strlen(str1) > strlen(str2)) return str1;
                        return str2;
                    }));
    return result;
}

void *testWithAggregateWithSeed(ArrayList arr, char *seed) {
    Linq *lq = From(arr);
    void *result = 
        lq
        ->AGGREGATE_WITH_SEED(seed,
                              lambda(void *, (void *item1, void *item2) {
                                  char *str1 = (char *)item1;
                                  char *str2 = (char *)item2;
                                  if (strlen(str1) > strlen(str2)) return str1;
                                  return str2;
                              }));
    return result;
}

void *testWithAggregateWithSeedBy(ArrayList arr, char *seed) {
    Linq *lq = From(arr);
    void *result = 
        lq
        ->AGGREGATE_WITH_SEEDBY(seed,
                                lambda(void *, (void *item1, void *item2) {
                                    char *str1 = (char *)item1;
                                    char *str2 = (char *)item2;
                                    if (strlen(str1) > strlen(str2)) return str1;
                                    return str2;
                                    }), 
                                lambda(void *, (void *item) {
                                    /* convert to uppercase */
                                    char *result = newStr((char *)item);
                                    for(int i = 0; result[i] != '\0'; i++) {
                                        if (result[i] >= 'a' && result[i] <= 'z') {
                                            result[i] = result[i] - 32;
                                        }
                                    }
                                    return result;
                                }));
    return result;
}

ArrayList testWithConcat(ArrayList concatArrSrc, ArrayList concatArrDst) {
    Linq *lq = From(concatArrSrc);
    void *result = 
        lq
        ->CONCAT(From(concatArrDst))
        ->TO_ARRAY();
    return result;
}


bool testWithSequenceEqual(ArrayList seqSrc, ArrayList seqDst) {
    Linq *lq = From(seqSrc);
    bool result = 
        lq
        ->SEQUENCE_EQUAL(
                        From(seqDst),
                        lambda(bool, (void *item1, void *item2) {
                            int a = TOINT(item1);
                            int b = TOINT(item2);
                            return a == b;
                        }));
    return result;
}

ArrayList testWithTake(ArrayList takeArr, int num) {
    Linq *lq = From(takeArr);
    return lq->TAKE(3)->TO_ARRAY();
}

ArrayList testWithTakeWhile(ArrayList takeWhileArr) {
    Linq *lq = From(takeWhileArr);
    ArrayList result = 
        lq
        ->TAKE_WHILE( 
                    lambda(bool, (void *item) {
                        int i = TOINT(item);
                        return i < 7;
                    }))
        ->TO_ARRAY();
    return result;
}

ArrayList testWithTakeExcept(ArrayList takeExceptArr) {
    Linq *lq = From(takeExceptArr);
    ArrayList result = 
        lq
        ->TAKE_EXCEPT_LAST(3)
        ->TO_ARRAY();

    return result;
}

ArrayList testWithTakeFrom(ArrayList takeFromArr) {
    Linq *lq = From(takeFromArr);
    ArrayList result = 
        lq
        ->TAKE_FROM_LAST(5)
        ->TO_ARRAY();

    return result;
}

ArrayList testWithAlternateBefore(ArrayList alternateBeforeArr) {
    int *x = newInt(-1);

    Linq *lq = From(alternateBeforeArr);
    ArrayList result = 
        lq
        ->ALTERNATE_BEFORE(x)
        ->TO_ARRAY();

    return result;
}

ArrayList testWithAlternateAfter(ArrayList alternateAfterArr) {
    int *x = newInt(-1);

    Linq *lq = From(alternateAfterArr);
    ArrayList result = 
        lq
        ->ALTERNATE_AFTER(x)
        ->TO_ARRAY();

    return result;
}

ArrayList testWithShuffle(ArrayList shuffleArr) {
    Linq *lq = From(shuffleArr);
    ArrayList result = 
        lq
        ->SHUFFLE()
        ->TO_ARRAY();

    return result;
}

ArrayList testWithSlice(ArrayList sliceArr) {
    Linq *lq = From(sliceArr);
    ArrayList result = 
        lq
        ->SLICE(2, 3)
        ->TO_ARRAY();

    return result;
}

ArrayList testWithPrint(ArrayList printArr) {
    Linq *lq = From(printArr);
    lq
    ->PRINT("->", lambda(char *, (int idx, void *item) {
                return (char *)item; })
           );
}

ArrayList testWithPrintln(ArrayList printlnArr) {
    Linq *lq = From(printlnArr);
    lq
    ->PRINTLN(lambda(char *, (int idx, void *item) {
                struct dummyStruct *dummy = (struct dummyStruct *)item;
                return newStr("%s:%d", dummy->str, dummy->val); })
           );
}

ArrayList testWithPrintln2(ArrayList printlnArr) {
    Linq *lq = From(printlnArr);
    lq
    ->PRINTLN(lambda(char *, (int idx, void *item) {
                return newStr("%d:%d", idx, TOINT(item)); }
             ));
}

ArrayList testWithPrintln3() {
    Linq *lq = Range(0, 20);
    lq
    ->WHERE(lambda(bool, (void *item) { return TOINT(item) % 3 == 0; }))
    ->SELECT(lambda(void *, (void *item) {
                int x = TOINT(item) * 10;
                return newInt(x);
                }))
    ->PRINTLN(lambda(char *, (int idx, void *item) {
                return newStr("%d:%d", idx, TOINT(item)); }
             ));
}

int main(int argc, char **argv) {
    GC_INIT();

    int i = 0;

    char *str1 = "huang", *str2 = "hai", *str3 = "feng", *str4 = "welcome";

    ArrayList array = arrlist_new();
    arrlist_append(array, str1);
    arrlist_append(array, str2);
    arrlist_append(array, str3);

    ArrayList array2 = arrlist_new();
    arrlist_append(array2, str1);
    arrlist_append(array2, str2);
    arrlist_append(array2, str4);

    ArrayList result = NULL;
    printf("\n====================NORMAL(1)====================\n");
    result = testWithNormal(array);
    for(i = 0; i < arrlist_size(result); i++) {
        printf("%s\n", arrlist_get(result, i));
    }

    printf("\n====================NORMAL(2)====================\n");
    result = testWithNormal2();
    for(i = 0; i < arrlist_size(result); i++) {
        int *a = arrlist_get(result, i);
        printf("%d\n", *a);
    }

    printf("\n====================UNION====================\n");
    Linq *unionLq_other = From(array2);
    ArrayList result2 = testWithUnion(array, unionLq_other);
    for(i = 0; i < arrlist_size(result2); i++) {
        printf("%s\n", arrlist_get(result2, i));
    }

    printf("\n====================INTERSECT====================\n");
    Linq *intersectLq = From(array2);
    ArrayList result3 = testWithIntersect(array, intersectLq);
    for(i = 0; i < arrlist_size(result3); i++) {
        printf("%s\n", arrlist_get(result3, i));
    }

    int i1 = 10, i2 = 20, i3 = 35, i4 = 40;
    float f1 = 10.0, f2 = 34.5, f3 = 67.8, f4 = 42.1;

    ArrayList numberArr1 = arrlist_new();
    arrlist_append(numberArr1, &i1);
    arrlist_append(numberArr1, &i2);
    arrlist_append(numberArr1, &i3);
    arrlist_append(numberArr1, &i4);

    ArrayList numberArr2 = arrlist_new();
    arrlist_append(numberArr2, &f1);
    arrlist_append(numberArr2, &f2);
    arrlist_append(numberArr2, &f3);
    arrlist_append(numberArr2, &f4);

    printf("\n====================SUM_INTS====================\n");
    int int_result  = testWithSumInts(numberArr1);
    printf("%d\n", int_result);

    printf("\n====================SUM_FLOATS====================\n");
    float float_result  = testWithSumFloats(numberArr2);
    printf("%g\n", float_result);

    printf("\n====================MAX_INTS====================\n");
    int maxint_result  = testWithMaxInts(numberArr1);
    printf("%d\n", maxint_result);

    printf("\n====================MAX_FLOATS====================\n");
    float maxfloat_result  = testWithMaxFloats(numberArr2);
    printf("%g\n", maxfloat_result);

    printf("\n====================MIN_INTS====================\n");
    int minint_result  = testWithMinInts(numberArr1);
    printf("%d\n", minint_result);

    printf("\n====================MIN_FLOATS====================\n");
    float minfloat_result  = testWithMinFloats(numberArr2);
    printf("%g\n", minfloat_result);

    printf("\n====================AVERAGE_INTS====================\n");
    float average_int_result  = testWithAverageInts(numberArr1);
    printf("%g\n", average_int_result);

    printf("\n====================AVERAGE_FLOATS====================\n");
    float average_float_result  = testWithAverageFloats(numberArr2);
    printf("%g\n", average_float_result);

    printf("\n====================MAX====================\n");
    void *max_result  = testWithMax(numberArr1);
    printf("%d\n", TOINT(max_result));

    char *numstr1 = "10.3", *numstr2 = "4.8", *numstr3 = "67.8", *numstr4 = "42.1";
    ArrayList strArr2 = arrlist_new();
    arrlist_append(strArr2, numstr1);
    arrlist_append(strArr2, numstr2);
    arrlist_append(strArr2, numstr3);
    arrlist_append(strArr2, numstr4);

    printf("\n====================MIN====================\n");
    void *min_result  = testWithMin(strArr2);
    printf("%s\n", (char *)min_result);


    printf("\n====================Prepend====================\n");
    ArrayList arrPrepend = arrlist_new();
    arrlist_append(arrPrepend, numstr1);
    arrlist_append(arrPrepend, numstr2);
    arrlist_append(arrPrepend, numstr3);
    ArrayList prepend_result  = testWithPrepend(arrPrepend);
    for (int i = 0; i < arrlist_size(prepend_result); i++) {
        printf("%s\n", (char *)arrlist_get(prepend_result, i));
    }

    printf("\n====================Append====================\n");
    ArrayList arrAppend = arrlist_new();
    arrlist_append(arrAppend, numstr1);
    arrlist_append(arrAppend, numstr2);
    arrlist_append(arrAppend, numstr3);
    ArrayList append_result  = testWithAppend(arrAppend);
    for (int i = 0; i < arrlist_size(append_result); i++) {
        printf("%s\n", (char *)arrlist_get(append_result, i));
    }


    printf("\n====================SORT(1)====================\n");
    ArrayList arrToSort1 = arrlist_new();
    arrlist_append(arrToSort1, str1); /* huang */
    arrlist_append(arrToSort1, str4); /* welcome */
    arrlist_append(arrToSort1, str3); /* feng */
    arrlist_append(arrToSort1, str2); /* hai */
    result = testWithSort1(arrToSort1);
    for(i = 0; i < arrlist_size(result); i++) {
        printf("%s\n", arrlist_get(result, i));
    }

    printf("\n====================SORT(2)====================\n");
    ArrayList arrToSort2 = arrlist_new();
    arrlist_append(arrToSort2, numstr1);
    arrlist_append(arrToSort2, numstr2);
    arrlist_append(arrToSort2, numstr3);
    arrlist_append(arrToSort2, numstr4);
    result = testWithSort2(arrToSort2);
    for(i = 0; i < arrlist_size(result); i++) {
        printf("%s\n", arrlist_get(result, i));
    }

    printf("\n====================SORT_DESC(1)====================\n");
    ArrayList arrToSort3 = arrlist_new();
    arrlist_append(arrToSort3, str1); /* huang */
    arrlist_append(arrToSort3, str4); /* welcome */
    arrlist_append(arrToSort3, str3); /* feng */
    arrlist_append(arrToSort3, str2); /* hai */

    result = testWithSortDesc1(arrToSort3);
    for(i = 0; i < arrlist_size(result); i++) {
        printf("%s\n", arrlist_get(result, i));
    }

    printf("\n====================SORT_DESC(2)====================\n");
    ArrayList arrToSort4 = arrlist_new();
    arrlist_append(arrToSort4, numstr1);
    arrlist_append(arrToSort4, numstr2);
    arrlist_append(arrToSort4, numstr3);
    arrlist_append(arrToSort4, numstr4);

    result = testWithSortDesc2(arrToSort4);
    for(i = 0; i < arrlist_size(result); i++) {
        printf("%s\n", arrlist_get(result, i));
    }

    printf("\n====================Range====================\n");
    Linq *rangeLq = Range(3, 5);
    ArrayList rangeArr = rangeLq->ToArray(rangeLq);
    for (int i = 0; i < arrlist_size(rangeArr); i++) {
        printf("%d\n", TOINT(arrlist_get(rangeArr, i)));
    }

    printf("\n====================RangeWithStep====================\n");
    Linq *rangeStepLq = RangeWithStep(3, 3, 5);
    ArrayList rangeStepArr = rangeStepLq->ToArray(rangeStepLq);
    for (int i = 0; i < arrlist_size(rangeStepArr); i++) {
        printf("%d\n", TOINT(arrlist_get(rangeStepArr, i)));
    }

    printf("\n====================RangeDown====================\n");
    Linq *rangeDownLq = RangeDown(3, 5);
    ArrayList rangeDownArr = rangeDownLq->ToArray(rangeDownLq);
    for (int i = 0; i < arrlist_size(rangeDownArr); i++) {
        printf("%d\n", TOINT(arrlist_get(rangeDownArr, i)));
    }

    printf("\n====================RangeWithStep====================\n");
    Linq *rangeDownStepLq = RangeDownWithStep(3, 3, 5);
    ArrayList rangeDownStepArr = rangeDownStepLq->ToArray(rangeDownStepLq);
    for (int i = 0; i < arrlist_size(rangeDownStepArr); i++) {
        printf("%d\n", TOINT(arrlist_get(rangeDownStepArr, i)));
    }

    printf("\n====================Repeat====================\n");
    struct Person{
        char name[32];
        int age;
    };
    struct Person *p = GC_malloc(sizeof(struct Person));
    strcpy(p->name, "HuangHaiFeng");
    p->age = 40;

    Linq *repeatLq = Repeat(p, sizeof(struct Person), 3);
    ArrayList repeatArr = repeatLq->ToArray(repeatLq);
    for (int i = 0; i < arrlist_size(repeatArr); i++) {
        struct Person *item = (struct Person *)arrlist_get(repeatArr, i);
        printf("name=%s, age=%d\n", item->name, item->age);
    }

    printf("\n====================GroupBy(1)====================\n");
    /*
         {"Owner" : "Google",    "Name" : "Chrome"}
         {"Owner" : "Microsoft", "Name" : "Windows"}
         {"Owner" : "Google",    "Name" : "GMail"}
         {"Owner" : "Microsoft", "Name" : "VisualStudio"}
         {"Owner" : "Google",    "Name" : "GMail"}
         {"Owner" : "Microsoft", "Name" : "XBox"}
         {"Owner" : "Google",    "Name" : "GMail"}
         {"Owner" : "Google",    "Name" : "AppEngine"}
         {"Owner" : "Intel",     "Name" : "ParallelStudio"}
         {"Owner" : "Intel",     "Name" : "VTune"}
         {"Owner" : "Microsoft", "Name" : "Office"}
         {"Owner" : "Intel",     "Name" : "Edison"}
         {"Owner" : "Google",    "Name" : "GMail"}
         {"Owner" : "Microsoft", "Name" : "PowerShell"}
         {"Owner" : "Google",    "Name" : "GMail"}
         {"Owner" : "Google",    "Name" : "GDrive"}
     */
    struct ProductInfo *pi1 = GC_malloc(sizeof(struct ProductInfo));
    strcpy(pi1->Owner, "Google"); strcpy(pi1->Name, "Chrome");

    struct ProductInfo *pi2 = GC_malloc(sizeof(struct ProductInfo));
    strcpy(pi2->Owner, "Microsoft"); strcpy(pi2->Name, "Windows");

    struct ProductInfo *pi3 = GC_malloc(sizeof(struct ProductInfo));
    strcpy(pi3->Owner, "Google"); strcpy(pi3->Name, "GMail");

    struct ProductInfo *pi4 = GC_malloc(sizeof(struct ProductInfo));
    strcpy(pi4->Owner, "Microsoft"); strcpy(pi4->Name, "VisualStudio");

    struct ProductInfo *pi5 = GC_malloc(sizeof(struct ProductInfo));
    strcpy(pi5->Owner, "Google"); strcpy(pi5->Name, "GMail");

    struct ProductInfo *pi6 = GC_malloc(sizeof(struct ProductInfo));
    strcpy(pi6->Owner, "Microsoft"); strcpy(pi6->Name, "XBox");

    struct ProductInfo *pi7 = GC_malloc(sizeof(struct ProductInfo));
    strcpy(pi7->Owner, "Google"); strcpy(pi7->Name, "GMail");

    struct ProductInfo *pi8 = GC_malloc(sizeof(struct ProductInfo));
    strcpy(pi8->Owner, "Google"); strcpy(pi8->Name, "AppEngine");

    struct ProductInfo *pi9 = GC_malloc(sizeof(struct ProductInfo));
    strcpy(pi9->Owner, "Intel"); strcpy(pi9->Name, "ParallelStudio");

    struct ProductInfo *pi10 = GC_malloc(sizeof(struct ProductInfo));
    strcpy(pi10->Owner, "Intel"); strcpy(pi10->Name, "VTune");

    struct ProductInfo *pi11 = GC_malloc(sizeof(struct ProductInfo));
    strcpy(pi11->Owner, "Microsoft"); strcpy(pi11->Name, "Office");

    struct ProductInfo *pi12 = GC_malloc(sizeof(struct ProductInfo));
    strcpy(pi12->Owner, "Intel"); strcpy(pi12->Name, "Edison");

    struct ProductInfo *pi13 = GC_malloc(sizeof(struct ProductInfo));
    strcpy(pi13->Owner, "Google"); strcpy(pi13->Name, "GMail");

    struct ProductInfo *pi14 = GC_malloc(sizeof(struct ProductInfo));
    strcpy(pi14->Owner, "Microsoft"); strcpy(pi14->Name, "PowerShell");

    struct ProductInfo *pi15 = GC_malloc(sizeof(struct ProductInfo));
    strcpy(pi15->Owner, "Google"); strcpy(pi15->Name, "GMail");

    struct ProductInfo *pi16 = GC_malloc(sizeof(struct ProductInfo));
    strcpy(pi16->Owner, "Google"); strcpy(pi16->Name, "GDrive");

    ArrayList groupByArr = arrlist_new();
    arrlist_append(groupByArr, pi1);
    arrlist_append(groupByArr, pi2);
    arrlist_append(groupByArr, pi3);
    arrlist_append(groupByArr, pi4);
    arrlist_append(groupByArr, pi5);
    arrlist_append(groupByArr, pi6);
    arrlist_append(groupByArr, pi7);
    arrlist_append(groupByArr, pi8);
    arrlist_append(groupByArr, pi9);
    arrlist_append(groupByArr, pi10);
    arrlist_append(groupByArr, pi11);
    arrlist_append(groupByArr, pi12);
    arrlist_append(groupByArr, pi13);
    arrlist_append(groupByArr, pi14);
    arrlist_append(groupByArr, pi15);
    arrlist_append(groupByArr, pi16);
    ArrayList groupByResult = testWithGroupBy(groupByArr);

    for (int i = 0; i < arrlist_size(groupByResult); i++) {
        Group *grp = (Group *)arrlist_get(groupByResult, i);
        printf("Group Key=[%s]\n", (char *)grp->Key);
        ArrayList value = grp->Array;
        for (int j = 0; j < arrlist_size(value); j++) {
            printf("\tvalue=[%s]\n", (char *)arrlist_get(value, j));
        }
    }

    printf("\n====================GroupBy(2)====================\n");
    ArrayList groupByArr2 = arrlist_new();
    for (int i = 0; i < 9; i++) {
        int *x = newInt(i);
         arrlist_append(groupByArr2, x);
    }

    ArrayList groupByResult2 = testWithGroupBy2(groupByArr2);

    for (int i = 0; i < arrlist_size(groupByResult2); i++) {
        Group *grp = (Group *)arrlist_get(groupByResult2, i);
        printf("Group Key=[%s]\n", (char *)grp->Key);
        ArrayList value = grp->Array;
        for (int j = 0; j < arrlist_size(value); j++) {
            printf("\tvalue=[%d]\n", TOINT(arrlist_get(value, j)));
        }
    }

    printf("\n====================JOINStr====================\n");
    ArrayList str_array = arrlist_new();
    arrlist_append(str_array, str1);
    arrlist_append(str_array, str2);
    arrlist_append(str_array, str3);
    arrlist_append(str_array, str4);
    char *strResult = testWithJoinStr(str_array);
    printf("strResult=[%s]\n", strResult);

    printf("\n====================JOIN====================\n");
    struct joinOwner *joinOwner1 = GC_malloc(sizeof(struct joinOwner));
    strcpy(joinOwner1->Name, "Hedlund, Magnus");

    struct joinOwner *joinOwner2 = GC_malloc(sizeof(struct joinOwner));
    strcpy(joinOwner2->Name, "Adams, Terry");

    struct joinOwner *joinOwner3 = GC_malloc(sizeof(struct joinOwner));
    strcpy(joinOwner3->Name, "Weiss, Charlotte");

    ArrayList joinOwnerArr = arrlist_new();
    arrlist_append(joinOwnerArr, joinOwner1);
    arrlist_append(joinOwnerArr, joinOwner2);
    arrlist_append(joinOwnerArr, joinOwner3);

    struct joinPets *joinPets1 = GC_malloc(sizeof(struct joinPets));
    strcpy(joinPets1->Name, "Barley");
    joinPets1->Age = 8;
    joinPets1->Owner = joinOwner2;

    struct joinPets *joinPets2 = GC_malloc(sizeof(struct joinPets));
    strcpy(joinPets2->Name, "Boots");
    joinPets2->Age = 4;
    joinPets2->Owner = joinOwner2;

    struct joinPets *joinPets3 = GC_malloc(sizeof(struct joinPets));
    strcpy(joinPets3->Name, "Whiskers");
    joinPets3->Age = 1;
    joinPets3->Owner = joinOwner3;

    struct joinPets *joinPets4 = GC_malloc(sizeof(struct joinPets));
    strcpy(joinPets4->Name, "Daisy");
    joinPets4->Age = 4;
    joinPets4->Owner = joinOwner1;

    ArrayList joinPetsArr = arrlist_new();
    arrlist_append(joinPetsArr, joinPets1);
    arrlist_append(joinPetsArr, joinPets2);
    arrlist_append(joinPetsArr, joinPets3);
    arrlist_append(joinPetsArr, joinPets4);

    Linq *petsLq = From(joinPetsArr);
    ArrayList joinResult = testWithJoin(petsLq, joinOwnerArr, joinPetsArr);
    for (int i = 0; i < arrlist_size(joinResult); i++) {
        printf("%s\n", (char *)arrlist_get(joinResult, i));
    }

    printf("\n====================GROUP_JOIN====================\n");
    ArrayList groupJoinArr_outer = arrlist_new();
    for (int i = 0; i < 3; i++) {
        int *x = newInt(i);
         arrlist_append(groupJoinArr_outer, x);
    }

    ArrayList groupJoinArr_inner = arrlist_new();
    for (int i = 1; i < 10; i++) {
        int *x = newInt(i);
         arrlist_append(groupJoinArr_inner, x);
    }
    Linq *groupJoin_innerLq = From(groupJoinArr_inner);

    ArrayList groupJoinResult = testWithGroupJoin(groupJoin_innerLq, groupJoinArr_outer);
    for (int i = 0; i < arrlist_size(groupJoinResult); i++) {
        struct GroupJoin_KeyValue *kv = arrlist_get(groupJoinResult, i);
        printf("key = %d, value=%d\n", TOINT(kv->Key), TOINT(kv->Value));
    }


    printf("\n====================Aggregate====================\n");
    ArrayList aggArr1 = arrlist_new();
    arrlist_append(aggArr1, str1); /* "huang" */
    arrlist_append(aggArr1, str4); /* "welcome" */
    arrlist_append(aggArr1, str2); /* "hai" */
    arrlist_append(aggArr1, str3); /* "feng" */
    char *aggResult1 = (char *)testWithAggregate(aggArr1);
    printf("result = [%s]\n", aggResult1);


    printf("\n====================Aggregate With Seed====================\n");
    ArrayList aggArr2 = arrlist_new();
    arrlist_append(aggArr2, str1); /* "huang" */
    arrlist_append(aggArr2, str4); /* "welcome" */
    arrlist_append(aggArr2, str2); /* "hai" */
    arrlist_append(aggArr2, str3); /* "feng" */
    char *seed2 = "passionfruit";
    char *aggResult2 = (char *)testWithAggregateWithSeed(aggArr2, seed2);
    printf("result = [%s]\n", aggResult2);


    printf("\n====================Aggregate With Seed By====================\n");
    ArrayList aggArr3 = arrlist_new();
    arrlist_append(aggArr3, str1); /* "huang" */
    arrlist_append(aggArr3, str4); /* "welcome" */
    arrlist_append(aggArr3, str2); /* "hai" */
    arrlist_append(aggArr3, str3); /* "feng" */
    char *seed3 = "banana";
    char *aggResult3 = (char *)testWithAggregateWithSeedBy(aggArr3, seed3);
    printf("result = [%s]\n", aggResult3);


    printf("\n====================Concat====================\n");
    ArrayList concatArrSrc = arrlist_new();
    for (int i = 1; i < 4; i++) {
        int *x = newInt(i);
         arrlist_append(concatArrSrc, x);
    }

    ArrayList concatArrDst = arrlist_new();
    for (int i = 4; i < 6; i++) {
        int *x = newInt(i);
        arrlist_append(concatArrDst, x);
    }

    ArrayList concatResult = testWithConcat(concatArrSrc, concatArrDst);
    for (int i = 0; i < arrlist_size(concatResult); i++) {
        printf("%d\n", TOINT(arrlist_get(concatResult, i)));
    }


    printf("\n====================Sequence Equal====================\n");
    ArrayList seqSrc = arrlist_new();
    for (int i = 1; i < 4; i++) {
        int *x = newInt(i);
        arrlist_append(seqSrc, x);
    }

    ArrayList seqDst = arrlist_new();
    for (int i = 1; i < 4; i++) {
        int *x = newInt(i);
        arrlist_append(seqDst, x);
    }

    bool isEqual = testWithSequenceEqual(seqSrc, seqDst);
    if (isEqual) {
        printf("Sequence is equal\n");
    }

    printf("\n====================Take====================\n");
    ArrayList takeArr = arrlist_new();
    for (int i = 0; i < 10; i++) {
        int *x = newInt(i);
        arrlist_append(takeArr, x);
    }

    ArrayList takeResult = testWithTake(takeArr, 3);
    for (int i = 0; i < arrlist_size(takeResult); i++) {
        printf("%d\n", TOINT(arrlist_get(takeResult, i)));
    }

    printf("\n====================TakeWhile====================\n");
    ArrayList takeWhileArr = arrlist_new();
    for (int i = 0; i < 10; i++) {
        int *x = newInt(i);
        arrlist_append(takeWhileArr, x);
    }

    ArrayList takeWhileResult = testWithTakeWhile(takeWhileArr);
    for (int i = 0; i < arrlist_size(takeWhileResult); i++) {
        printf("%d\n", TOINT(arrlist_get(takeWhileResult, i)));
    }

    printf("\n====================TakeExceptLast====================\n");
    ArrayList takeExceptArr = arrlist_new();
    for (int i = 0; i < 10; i++) {
        int *x = newInt(i);
        arrlist_append(takeExceptArr, x);
    }

    ArrayList takeExceptResult = testWithTakeExcept(takeWhileArr);
    for (int i = 0; i < arrlist_size(takeExceptResult); i++) {
        printf("%d\n", TOINT(arrlist_get(takeExceptResult, i)));
    }

    printf("\n====================TakeFromLast====================\n");
    ArrayList takeFromArr = arrlist_new();
    for (int i = 0; i < 10; i++) {
        int *x = newInt(i);
        arrlist_append(takeFromArr, x);
    }

    ArrayList takeFromResult = testWithTakeFrom(takeFromArr);
    for (int i = 0; i < arrlist_size(takeFromResult); i++) {
        printf("%d\n", TOINT(arrlist_get(takeFromResult, i)));
    }

    printf("\n====================AlternateBefore====================\n");
    ArrayList alternateBeforeArr = arrlist_new();
    for (int i = 0; i < 3; i++) {
        int *x = newInt(i);
        arrlist_append(alternateBeforeArr, x);
    }

    ArrayList alternateBeforeResult = testWithAlternateBefore(alternateBeforeArr);
    for (int i = 0; i < arrlist_size(alternateBeforeResult); i++) {
        printf("%d\n", TOINT(arrlist_get(alternateBeforeResult, i)));
    }

    printf("\n====================AlternateAfter====================\n");
    ArrayList alternateAfterArr = arrlist_new();
    for (int i = 0; i < 3; i++) {
        int *x = newInt(i);
        arrlist_append(alternateAfterArr, x);
    }


    ArrayList alternateAfterResult = testWithAlternateAfter(alternateAfterArr);
    for (int i = 0; i < arrlist_size(alternateAfterResult); i++) {
        printf("%d\n", TOINT(arrlist_get(alternateAfterResult, i)));
    }

    printf("\n====================Shuffle====================\n");
    ArrayList shuffleArr = arrlist_new();
    for (int i = 0; i < 10; i++) {
        int *x = newInt(i * 2 + 3);
         arrlist_append(shuffleArr, x);
    }
    ArrayList shuffleResult = testWithShuffle(shuffleArr);
    for (int i = 0; i < arrlist_size(shuffleResult); i++) {
        printf("%d\n", TOINT(arrlist_get(shuffleResult, i)));
    }
    

    printf("\n====================Slice====================\n");
    ArrayList sliceArr = arrlist_new();
    for (int i = 0; i < 10; i++) {
        int *x = newInt(i);
         arrlist_append(sliceArr, x);
    }
    ArrayList sliceResult = testWithSlice(sliceArr);
    for (int i = 0; i < arrlist_size(sliceResult); i++) {
        printf("%d\n", TOINT(arrlist_get(sliceResult, i)));
    }

    printf("\n====================Print====================\n");
    ArrayList printArr = arrlist_new();
    arrlist_append(printArr, str1);
    arrlist_append(printArr, str2);
    arrlist_append(printArr, str3);
    arrlist_append(printArr, str4);
    testWithPrint(printArr);

    printf("\n====================Println(1)====================\n");
    ArrayList printlnArr = arrlist_new();
    struct dummyStruct *dummy1 = GC_malloc(sizeof(struct dummyStruct));
    dummy1->str = "foo";
    dummy1->val = 1;
    arrlist_append(printlnArr, dummy1);

    struct dummyStruct *dummy2 = GC_malloc(sizeof(struct dummyStruct));
    dummy2->str = "bar";
    dummy2->val = 3;
    arrlist_append(printlnArr, dummy2);
    testWithPrintln(printlnArr);


    printf("\n====================Println(2)====================\n");
    ArrayList println2Arr = arrlist_new();
    for (int i = 0; i < 10; i++) {
         arrlist_append(println2Arr, newInt(i));
    }
    testWithPrintln2(println2Arr);

    printf("\n====================Println(3)====================\n");
    testWithPrintln3();



    printf("\n====================Cycle & ForEach====================\n");
    ArrayList arrayCycle = arrlist_new();
    arrlist_append(arrayCycle, str1);
    arrlist_append(arrayCycle, str2);
    arrlist_append(arrayCycle, str3);

    Linq *lq = Cycle(arrayCycle, 3);
    printf("Cycle count =[%d]\n", lq->COUNT());
    lq->FOREACH(lambda(void, (int idx, void *item) {
                    printf("%d:%s\n", idx, (char *)item);
               }));


    printf("\n====================Match(1)====================\n");
    char* stringInput1 = "___ abc123def ___ ghi456 ___";
    lq = Matches(true, stringInput1, "[a-z]*([0-9]+)([a-z]*)");
    lq->ForEach(lq, lambda(void, (int idx, void *item) {
                    printf("[%d] : %s\n", idx, (char *)item);
               }));

    printf("\n====================Match(2)====================\n");
    char* stringInput2 = "text123";
    lq = Matches(true, stringInput2, "([a-z]+)([0-9]+)");
    lq->ForEach(lq, lambda(void, (int idx, void *item) {
                    printf("[%d] : %s\n", idx, (char *)item);
               }));


    printf("\n\n");
    return 0;
}

