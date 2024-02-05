import "./tests/hello.ru";
import "./tests/help.ru";

khaaka B -> A {
    method() {
        elaan closure <- super.method;
        closure(); // chhaaps "A".
    }
}

elaan b <- B();
b.method();

tafaaul loop(number) {
    shoro (elaan i <- 0; i < number; i <- i + 1) {
        chhaap i;
    }
    lautana "Done";
}

chhaap loop(5);

agr (glt) {
    chhaap "nouman";
}
warna {
    chhaap "amir";
}

elaan i <- 0;
jbtk (i < 5) {
    chhaap i;
    i <- i + 1;
}

khaaka C {
    method() {
        chhaap this.name;
    }
}

elaan c <- C();
c.name <- "ha ha ha";
c.method();