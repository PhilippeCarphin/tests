trg = dbinterface.out
src = main.c

LDLIBS = -lpthread -ldl -lsqlite3

test_db=test.db

bad_test_cmd=CREATE TABLE phil (a int, b int)

a=$(shell date +%s)
b=$(shell date +%M)
good_test_cmd=INSERT INTO phil (a,b) VALUES ($(a), $(b));

all:$(trg)

$(trg):$(src)
	gcc -o $@ $^ $(LDLIBS)

test:$(trg)
	@echo "This test is supposed to fail"
	./$(trg) $(test_db) "$(bad_test_cmd)"
	@echo "This test is supposed to pass"
	./$(trg) $(test_db) "$(good_test_cmd)"
