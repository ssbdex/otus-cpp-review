#include <stdio.h>
#include <stdlib.h>
int main() {
   int m, n;
   scanf("%d%d", &n, &m);
   double s = 0;
   double md = m;
   int div = 1;
   int oil = 0;
   while (s < n) {
      s = s + md / div;
      div += 2;
      oil += m;
   };
   double ans = (n - s) * (div - 2) + oil;
   printf("%.0lf\n", abs(ans + 0.49999999999));
}