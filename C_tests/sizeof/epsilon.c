#include <stdio.h>
#include <float.h>
void pr_candidate(float f)
{

      printf("candidate: %.6a\tcandidate+1.0f: %.6a\n",f, 1.0f + f);
}

int main(void){

    pr_candidate(0x0.000002p0);
    pr_candidate(0x0.000001fffffep0);
    pr_candidate(0x0.0000018p0);
    pr_candidate(0x0.000001000002p0);
    pr_candidate(0x0.000001p0);
}
