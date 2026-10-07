//SLIP - 3
//Q.1

#include <stdio.h>

int q[20], f=-1, r=-1;

void enqueue(int x){
    if(f==-1) f=0;
    q[++r]=x;
}

int dequeue(){
    return q[f++];
}

void bfs(int a[10][10], int n, int start){
    int visited[10]={0};

    enqueue(start);
    visited[start]=1;

    while(f<=r){
        int v=dequeue();
        printf("%d ",v);

        for(int i=0;i<n;i++){
            if(a[v][i]==1 && visited[i]==0){
                enqueue(i);
                visited[i]=1;
            }
        }
    }
}

int main(){
    int n,a[10][10];

    scanf("%d",&n);
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            scanf("%d",&a[i][j]);

    bfs(a,n,0);
    return 0;
}

//Q.2 - DBMS
//Q.1 -DBMS
//CREATE TABLE 
CREATE TABLE Student (
 s_no INT PRIMARY KEY,
 s_name CHAR(20) NOT NULL,
 address CHAR(25),
 class CHAR(10)
);

CREATE TABLE Teacher (
 t_no INT PRIMARY KEY,
 t_name CHAR(10) NOT NULL,
 qualification CHAR(10),
 experience INT
);

-- M-M RELATION
CREATE TABLE Student_Teacher (
 s_no INT REFERENCES Student(s_no),
 t_no INT REFERENCES Teacher(t_no),
 subject VARCHAR(20),
 marks_scored INT CHECK (marks_scored > 0),
 PRIMARY KEY(s_no, t_no)
);


//INSERT VALUES 
INSERT INTO Student VALUES
(1,'Om','Pune','SY'),
(2,'Amit','Mumbai','FY');

INSERT INTO Teacher VALUES
(101,'Sharma','MSc',10),
(102,'Patil','PhD',12);

INSERT INTO Student_Teacher VALUES
(1,101,'RDBMS',80),
(2,102,'DS',70);

//TRIGGER
CREATE OR REPLACE FUNCTION check_student()
RETURNS trigger AS $$
BEGIN
 IF NEW.s_no <= 0 THEN
  RAISE EXCEPTION 'Invalid Number';
 END IF;

 RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_student
BEFORE INSERT ON Student
FOR EACH ROW
EXECUTE FUNCTION check_student();

//Q.2 - PROCEDURE DBMS 
CREATE OR REPLACE PROCEDURE min_max(a INT, b INT)
AS $$
DECLARE
 mn INT;
 mx INT;
BEGIN
 mn := LEAST(a,b);
 mx := GREATEST(a,b);

 RAISE NOTICE 'Minimum = %', mn;
 RAISE NOTICE 'Maximum = %', mx;
END;
$$ LANGUAGE plpgsql;
