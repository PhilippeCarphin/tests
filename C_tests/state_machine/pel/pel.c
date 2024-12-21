struct Test {
    int id;
    int title;
    int input;
    int output;
};

typedef enum STATE {
    ST_HEADER,
    ST_INPUT,
    ST_OUTPUT,
} STATE;

int read_header(stream, test){
    while(true){
        line = readline();
        if(strlen(line) == 0){
            return;
        }
        const header = line.split('|')
        test.id = header[0].trim()
        test.title = header[1].trim()
    }
}

int read_input(stream, test){
    while(true){
        if(strlen(line) == 0){
            return;
        }
        test.input += line
    }
}

int read_output(stream, test){
    while(true){
        if(line.startswith("--")){
            tests.push({...test})
            test.input = '';
            test.output = '';
        }
        test.output += line;
    }
}

main(){
    while(true){
        tests.push(read_test(stream));
        tests.push(test

read_test(){
    test = new Test();
    read_header(stream, test);
    read_input(stream, test);
    read_output(stream, test);
    return test;
}
const int HEADER_STATE = 0;

STATE header_transitions(char *line){
    switch strlen(line){
        case 0: return ST_INPUT;
        default: return ST_HEADER;
    }
}


int main(int argc, char **argv){

    int state = 0;
    struct Test test;

    switch(state) {
        case ST_HEADER: // Header.
            state = header_transitions(line);
            header_action(line);
            if (line.length === 0) {
                state = 1
                break
            }
            const header = line.split('|')
            test.id = header[0].trim()
            test.title = header[1].trim()
            break
        case 1: // Input.
            if (line.length === 0) {
                state = 2
                break
            }
            test.input += line
            break
        case 2: // Output.
            if (line.startsWith('--')) {
                tests.push({...test})
                test.input = ''
                test.output = ''
                state = 0
                break
            }
            test.output += line
            break
