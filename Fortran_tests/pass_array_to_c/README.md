# Passing arrays from C to Fortran

## Functions

The main function of interest is `cprint_array_2d_memory` which prints
`ni` consecutive elements, then prints a `\n` and another `ni` elements.  It
does this `nj` times.

The other functions use different means of accessing the element at index 
`j*ni + i`.

## Row-major vs Column-major

C is said to be "Row Major" because if we consider `tab[i][j]` to be i-th row
j-th column.  Row major means elements of a row are together in memory meaning
that `&(tab[i][j+1]) == &tab[i][j] + 1`.

Because I think the `tab[i][j]` indexing for 2D is an abomination that should
never be used, I don't see C as row or column major but simply as
pan-major.

That is, if I have something that is conceptually 2D and I do
```
void set_table(int *table, int ni, int nj, i, j, value){
    table[i*nj + j] = value;
}
int get_table(int *table, int ni, int nj, i, j){
    return table[i*nj + j];
}
```
then I'm storing elements with the same `i` together (another way of saying it is that mat(i,j) and mat(i,j+1) are next to each other), AKA row major.
```
set_table(int *table, int ni, int nj, i, j, value){
    table[j*ni + i] = value
}
int get_table(int *table, int ni, int nj, i, j){
    return table[j*ni + i];
}
```
then I'm storing elements with the same `j` together, AKA column major.

Because FORTRAN's N-dimensionnal array indexing is not a forbidden syntax, the
way that syntax places elements in memory defines a major-ness for FORTRAN.

In FORTRAN, `array(i,j)` is next to `array(i+1,j)` in memory, :








