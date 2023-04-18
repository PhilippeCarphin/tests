CFLAGS += -Wall -g -std=gnu99
# Even if they're not needed for the particular test
LDFLAGS += -lm -ldl

%:
	gcc $(CFLAGS) $(LDFLAGS) $@.c -o $@
	./$@

clean:
	find . -maxdepth 1 -perm -a=x -type f | xargs rm

