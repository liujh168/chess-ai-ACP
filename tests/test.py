import subprocess, os

def run_cpp(name, param):
    proc = subprocess.Popen(name + param,
                        shell=True)
                        
    so, se = proc.communicate()

    return(str(so))

if __name__ == '__main__':
    os.system("g++ test.cpp")
    print(run_cpp("a ", "1 2 3 4 5"))