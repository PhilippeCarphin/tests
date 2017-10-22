#ifndef LOOKUP_STRUCT_H_
#define LOOKUP_STRUCT_H_

enum my_enum { A = 0, B = 1, C = 2};

struct the_struct {
	const char *name;
	int int_val;
	float float_val;
	enum my_enum enum_val;
};

struct the_struct *lookup_struct(const char *name, struct the_struct the_structs[]);

#endif
