//
//  main.m
//  Obj_C
//
//  Created by Philippe Carphin on 2016-12-02.
//  Copyright © 2016 Philippe Carphin. All rights reserved.
//

#import <Foundation/Foundation.h>

int main(int argc, const char * argv[]) {
    char *hello = nil;
    @autoreleasepool {
        // insert code here...
        NSLog(@"Hello, World!");
        
        NSString *phil = nil;
        
        if( phil == nil)
            printf("Phil is nil\n");
        
        phil = @"phil's string";
        
        printf("Phil's string has length %lu\n", (unsigned long)[phil length]);
        
        const char *cstring = nil;
        
        cstring = [phil UTF8String];
        
        printf("This is the cstring version : %s\n", cstring);
        
        hello = malloc(8);
        
        strcpy(hello,"HelloG");
        
    }
    
    printf("string hello is : %s\n", hello);
    return 0;
}
