#include <iostream>
#include <sys/file.h>
#include <unistd.h>

// 
class RAIIClass
{
    public:
        RAIIClass(const char *lock_path)
        :lock_path(lock_path)
        {
            std::cout << "Creating lock file : '" << lock_path << "'" << std::endl;
            lock_fd = open(lock_path, O_RDWR | O_CREAT, 0666); // open or create lockfile
            int result = flock(lock_fd, LOCK_EX | LOCK_NB);
            if(result == 0){
                std::cout << "Acquired lock on file : '" << lock_path << "'" << std::endl;
            } else {
                std::cout << "Could not acquire lock" << std::endl;
                throw std::runtime_error("OOPSIE DOOPSIE");
            }
        }

        ~RAIIClass(){
            std::cout << __PRETTY_FUNCTION__ << std::endl;
            if(lock_fd > 0){
                remove(lock_path);
                close(lock_fd);
            }
        }

    private:
        int lock_fd;
        const char *lock_path;

};

int main(void)
{
    try{

        RAIIClass a("demo_lock");

        throw std::runtime_error("OOPSIE");

    } catch(...){
        throw;
    }

}
