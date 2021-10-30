# Printf
Tema 1 - printf

+++++++Se va implemementa în limbajul de programare C funcția
int iocla_printf(const char *format, …), care acceptă specificatorii
listați mai jos(*), oferind comportament similar cu printf din 
biblioteca standard C+++++++++++++++++++++++++++++++++++++++++

Primul argument pe care il primeste printf este - format stringul,
el precizeaza ce anume va afisa apelul lui printf.
Fiecare specificatie e introdusa de % - folosirea % si a unui
specificator de conversie consuma 0/mai multe argumente.

*Specificatorii ce vor fi implementați sunt următorii:
%d întreg, convertit la reprezentare zecimală, cu semn;
%u întreg, convertit la reprezentare zecimală, fara semn;
%x întreg, convertit la reprezentare hexazecimală, fara semn;
%c caracter, convertit la reprezentarea ASCII;
%s pointer la un șir de caractere, ce va fi afișat neschimbat;

**In implementare a fot interzisa folosirea tuturor funcțiilor din 
biblioteca standard C din familia printf care oferă deja comportamentul
cerut. Acestea includ, dar nu sunt limitate la printf, fprintf, 
dprintf, sprintf, snprintf, vprintf, vfprintf, vdprintf, vsprintf, 
vsnprintf.
