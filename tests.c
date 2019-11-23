#include "bigint.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    int i;
       // , j;
    char buf[65536];
    bigint a[1], b[1], c[1], d[1], e[20];
    const char *text = "123456790123456790120987654320987654321";

    bigint_init(a);
    bigint_init(b);
    bigint_init(c);
    bigint_init(d);

    for (i = 0; i < 20; i++) bigint_init(e + i);

    bigint_from_str(a, text);
    bigint_from_str(b, "11111111111111111111");
    bigint_sqrt(c, a);
    assert(bigint_cmp(b, c) == 0);

    bigint_from_str(a, "1");
    bigint_from_word(b, 1);
    bigint_shift_left(a, a, 1 << 10);

    bigint_mul(c, a, a);
    bigint_sub(c, c, a);
    bigint_sub(c, c, a);
    bigint_add(c, c, b);

    bigint_sub(a, a, b);
    bigint_mul(d, a, a);

    assert(bigint_cmp(c, d) == 0);

    bigint_from_str_base(a, text, 10);

    i = strcmp(text, bigint_write(buf, sizeof(buf), a));
    assert(i == 0);

    bigint_from_str(a, "");
    bigint_from_str(b, "0");
    bigint_from_str(c, "-0");
    assert(bigint_cmp(a, b) == 0);
    assert(bigint_cmp(a, c) == 0);

    for (i = 0; i < 12345; i++){
        int x = rand() % 12345;
        int y = rand() % 12345;
        int shift = rand() % 1234;
        if (rand() & 1) x = -x;
        if (rand() & 1) y = -y;

        bigint_from_int(a, x);
        bigint_from_int(b, y);
        bigint_from_int(e + 0, x + y);
        bigint_from_int(e + 1, x - y);
        bigint_from_int(e + 2, x * y);

        if (y != 0){
            bigint_from_int(e + 3, x / y);
            bigint_from_int(e + 4, x % y);
        }

        bigint_from_int(e + 5, sqrt(x > 0 ? x : -x));
        bigint_from_int(e + 6, bigint_int_gcd(x, y));

        bigint_cpy(c, a);
        bigint_shift_left(a, a, shift);
        bigint_shift_right(a, a, shift);

        assert(bigint_cmp(a, c) == 0);

        bigint_add(e + 10, a, b);
        bigint_sub(e + 11, a, b);
        bigint_mul(e + 12, a, b);
        bigint_div(e + 13, a, b);
        bigint_mod(e + 14, a, b);
        bigint_sqrt(e + 15, a);
        bigint_gcd(e + 16, a, b);

        //for (j = 0; j < 7; j++){
        //    if (y == 0 && (j == 3 || j == 4)) continue;
        //    if (bigint_cmp(e + j, e + j + 10) != 0){
        //        printf("i %i, j %i failed for bigints %i, %i\n", i, j, x, y);
        //    }
        //    //assert(bigint_cmp(e + j, e + j + 10) == 0);
        //}
    }

    bigint_free(a);
    bigint_free(b);
    bigint_free(c);
    bigint_free(d);

    for (i = 0; i < 20; i++) bigint_free(e + i);

    puts("Internal tests passed");

    puts("Starting neo tests");

    bigint v[1], w[1], x[1], y[1], z[1];
    bigint result[1];

    bigint_init(v);
    bigint_init(w);
    bigint_init(x);
    bigint_init(y);
    bigint_init(z);
    bigint_init(result);

    //test 1 start
    bigint_from_str(v, "41483775933600000000");
    bigint_from_str(w, "414937759336");
    bigint_div(result, v, w);
    bigint_from_int(x, 99975899);
    assert(bigint_cmp(x, result) == 0);
    //test 1 end


    // test 2 start
    bigint_from_str(x, "4149377593366666666");
    char *hex = bigint_2hex(x);
    assert(strcmp(hex, "39958CEFD395DDAA") == 0);
    // test 2 end

    // test 3 start
    bigint_from_str(x, "5505505505505505050505");
    bigint_from_str(y, "5505505505505505000000");
    bigint_sub(result, x, y);
    bigint_from_int(z, 50505);
    assert(bigint_cmp(z, result) == 0);
    // test 3 end

    // test 4 start
    bigint_from_str(x, "55055055055055");
    bigint_from_str(y, "55055055055");
    bigint_mul(result, x, y);
    bigint_from_str(z, "3031059087112109081053025");
    assert(bigint_cmp(z, result) == 0);
    // test 4 end

    // test 5 start
    bigint_from_str(x, "10");
    bigint_from_str(y, "20");
    bigint_add(result, x, y);
    bigint_from_str(z, "30");
    assert(bigint_cmp(z, result) == 0);
    // test 5 end

    // test 6 start
    bigint_from_str(x, "10");
    bigint_from_str(y, "20");
    bigint_add(result, x, y);
    bigint_from_str(z, "40");
    assert(bigint_cmp(z, result) != 0);
    // test 6 end

    // test 7 start
    bigint_from_str(x, "55055055055055");
    bigint_from_str(y, "55055055");
    bigint_div(result, x, y);
    bigint_from_str(z, "1000000");
    assert(bigint_cmp(z, result) == 0);
    // test 7 end

    // test 8 start
    bigint_from_str(x, "1");
    bigint_from_str(y, "2");
    bigint_div(result, x, y);
    bigint_from_str(z, "0");
    assert(bigint_cmp(z, result) == 0);
    // test 8 end

    // test 9 start
    bigint_from_str(x, "2");
    bigint_from_str(y, "3");
    bigint_div(result, x, y);
    bigint_from_str(z, "0");
    assert(bigint_cmp(z, result) == 0);
    // test 9 end

    // test 10 start
    bigint_from_str(x, "5");
    bigint_from_str(y, "4");
    bigint_div(result, x, y);
    bigint_from_str(z, "1");
    assert(bigint_cmp(z, result) == 0);
    // test 10 end

    // test 11 start
    bigint_from_str(x, "5");
    bigint_from_str(y, "3");
    bigint_div(result, x, y);
    bigint_from_str(z, "1");
    assert(bigint_cmp(z, result) == 0);
    // test 11 end

    // test 12 start
    bigint_from_str(x, "-1");
    bigint_from_str(y, "3");
    bigint_div(result, x, y);
    bigint_from_str(z, "0");
    assert(bigint_cmp(z, result) == 0);
    // test 12 end

    // test 13 start
    bigint_from_str(x, "-11001000000");
    bigint_from_str(y, "86400");
    bigint_div(result, x, y);
    bigint_from_str(z, "-127326");
    assert(bigint_cmp(z, result) == 0);
    // test 13 end
    
    // test 14 start
    bigint_from_str(x, "5505.001");
    bigint_from_str(y, "55055,999");
    bigint_add(result, x, y);
    bigint_from_str(z, "60560");
    assert(bigint_cmp(z, result) == 0);
    // test 14 end

    // test 15 start
    bigint_from_str(x, "860593");
    bigint_from_str(y, "-201");
    bigint_mod(result, x, y);
    bigint_from_str(z, "112");
    assert(bigint_cmp(z, result) == 0);
    // test 15 end

    // test 16 start
    bigint_from_str(x, "20195283520469175757");
    bigint_from_str(y, "1048576");
    bigint_mod(result, x, y);
    bigint_from_str(z, "888269");
    assert(bigint_cmp(z, result) == 0);
    // test 16 end
   
    // test 17 start
    bigint_from_str(x, "-18224909727634776050312394179610579601844989529623334093909233530432892596607");
    bigint_from_str(y, "14954691977398614017");
    bigint_mod(result, x, y);
    bigint_from_str(z, "-3100049211437790421");
    assert(bigint_cmp(z, result) == 0);
    // test 17 end

    // test 18 start
    bigint_from_str(x, "3");
    bigint_from_str(y, "1");
    bigint_shift_right(result, x, 1);
    bigint_from_str(z, "1");
    assert(bigint_cmp(z, result) == 0);
    bigint_shift_left(result, y, 3);
    bigint_from_str(z, "8");
    assert(bigint_cmp(z, result) == 0);
    // test 18 end

    bigint_free(v);
    bigint_free(w);
    bigint_free(x);
    bigint_free(y);
    bigint_free(z);
    bigint_free(result);


    puts("Neo tests passed");


    return 0;
}

