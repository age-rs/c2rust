// RUN: %clang_xcheck -O2 -o %t %s %xcheck_runtime %fakechecks
// RUN: %t 2>&1 | FileCheck %s

#include <stdio.h>

#include <cross_checks.h>

struct Foo {
    int a;
    int b CROSS_CHECK("disabled");
};

int foo(struct Foo x CROSS_CHECK("default")) {
    return x.a + x.b;
}

int main() {
    struct Foo x = { 1000, 1337 };
    foo(x);
    return 0;
}
// CHECK: XCHECK(1):2090499946/0x7c9a7f6a
// CHECK: XCHECK(1):193491849/0x0b887389
// CHECK: XCHECK(3):1143276485240798846/0xfddbbe7eed5be7e
// CHECK: XCHECK(2):193491849/0x0b887389
// CHECK: XCHECK(4):8680820740569198935/0x7878787878787157
// CHECK: XCHECK(2):2090499946/0x7c9a7f6a
// CHECK: XCHECK(4):8680820740569200758/0x7878787878787876
