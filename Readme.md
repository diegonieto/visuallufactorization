# Introduction
This application perform a LU factorizarion matrix that can be visualized by Qt

![alt](./img/test.png)

# Building
```
meson builddir
ninja -C builddir
./builddir/visualLU
```

# Testing
```
mkdir -p subprojects
meson wrap install gtest
meson builddir -Dtests=true
```

# References
* https://courses.physics.illinois.edu/cs357/sp2020/notes/ref-9-linsys.html
