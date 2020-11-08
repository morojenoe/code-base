interface Task {
  id: string;
  priority: number;
  time?: number;
  job: () => Promise<void>;
}

interface Res {
  successCount: number; 
  // число — общее количество невыполненных задач  
  failedCount: number;
  // массив строк — идентификаторы взятых задач по очереди  
  tasks: string[];
  // число — количество проведённых в работе миллисекунд  
  timeSpent: number;  
}

class TaskManager {  
  tasks: Task[] = [];
  res: Res[];
  curTaskId: number;
  constructor(readonly N: number // общее число роботов-исполнителей (от 1 до 1024)  
  ) {
    this.res = [];
    for (let i = 0; i < N; ++i) {
      this.res.push({
        failedCount: 0,
        successCount: 0,
        tasks: [],
        timeSpent: 0
      });
    }
  }

  addToQueue(task: Task) {
    this.tasks.push({
      ...task, time: this.tasks.length
    });
  }
  
  run(): Promise<Res[]> {
    this.tasks.sort((a, b) => {
      if (a.priority === b.priority) {
        return a.time < b.time ? -1 : 1;
      }
      return a.priority > b.priority ? -1 : 1;
    });
    let p: Promise<void>[] = [];
    this.curTaskId = this.N;
    for (let i = 0; i < Math.min(this.tasks.length, this.N); ++i) {
      p.push(this.take(i, i));
    }
    
    return Promise.all(p).then(
      () => this.res
    );
  }

  take(robotId: number, taskId?: number): Promise<void> {
    if (taskId === undefined) {
      taskId = this.curTaskId++;
    }
    if (taskId >= this.tasks.length) {
      return Promise.resolve();
    }

    const start = new Date(Date.now());
    return this.tasks[taskId].job().then(
      () => {
        const end = new Date(Date.now());
        this.res[robotId].timeSpent += end.getTime() - start.getTime();
        this.res[robotId].tasks.push(this.tasks[taskId].id);
        this.res[robotId].successCount++;
        return this.take(robotId);
      },
      () => {
        const end = new Date(Date.now());
        this.res[robotId].timeSpent += end.getTime() - start.getTime();
        this.res[robotId].tasks.push(this.tasks[taskId].id);
        this.res[robotId].failedCount++;
        return this.take(robotId);
      }
    )
  }
}  

module.exports = { TaskManager };
