from threading import enumerate, Event, Thread, Condition

class Master(Thread):
    def __init__(self, max_work, cond):
        Thread.__init__(self, name = "Master")
        self.max_work = max_work
        self.work_available = work_available
        self.result_available = result_available

        self.cond = cond
    
    def set_worker(self, worker):
        self.worker = worker
    
    def run(self):
        for i in range(self.max_work):
            # generate work
            self.work = i
            # notify worker
            with self.cond:
                self.cond.notify()

            # get result
            with self.cond:
                self.cond.wait()
            
            if self.get_work() + 1 != self.worker.get_result():
                print ("oops")
            print ("%d -> %d" % (self.work, self.worker.get_result()))
    
    def get_work(self):
        return self.work

class Worker(Thread):
    def __init__(self, terminate, cond):
        Thread.__init__(self, name = "Worker")
        self.terminate = terminate
        self.cond = cond

    def set_master(self, master):
        self.master = master
    
    def run(self):
        while(True):
            # wait work
            with self.cond:
                self.cond.wait()

            if(terminate.is_set()): break
            # generate result
            self.result = self.master.get_work() + 1
            # notify master
            with self.cond:
                self.cond.notify()
    
    def get_result(self):
        return self.result

if __name__ ==  "__main__":
    # create shared objects
    terminate = Event()
    work_available = Event()
    result_available = Event()

    cond = Condition()
    
    # start worker and master
    w = Worker(terminate, cond)
    m = Master(10, cond)
    w.set_master(m)
    m.set_worker(w)
    w.start()
    m.start()

    # wait for master
    m.join()

    # wait for worker
    terminate.set()
    with cond:
        cond.notify()

    w.join()

    # print running threads for verification
    print(enumerate())

