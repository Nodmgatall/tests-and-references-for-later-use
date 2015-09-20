from _thread import start_new_thread

num_threads = 0

def print_thread_data(i,j,k):
    test = j * 10
    global num_threads
    for idx in range(test, test+ 10):
        print(i,idx,k)
    num_threads -= 1

num_threads += 1
start_new_thread(print_thread_data,("1",1,"lol"))
num_threads += 1
start_new_thread(print_thread_data,("2",2, "rofl"))

while num_threads > 0:
    pass
