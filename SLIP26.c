//SLIP - 26
//Q.1
#include<stdio.h>

int adj[10][10],visited[10],n;

void dfs(int v){
    int i;
    printf("%d ",v);
    visited[v]=1;

    for(i=0;i<n;i++){
        if(adj[v][i]==1 && visited[i]==0){
            dfs(i);
        }
    }
}

int main(){
    int i,j;

    printf("Enter number of vertices: ");
    scanf("%d",&n);

    printf("Enter adjacency matrix:\n");
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            scanf("%d",&adj[i][j]);
            visited[i]=0;
        }
    }

    printf("DFS Traversal: ");
    dfs(0);

    return 0;
}

//Q.2 - DBMS
// DBMS
//CREATE TABLE 

CREATE TABLE Item (
 itemno INT PRIMARY KEY,
 itemname VARCHAR(20),
 quantity INT
);

CREATE TABLE Supplier (
 supplierno INT PRIMARY KEY,
 suppliername VARCHAR(20),
 city VARCHAR(20)
);

CREATE TABLE Item_Supplier (
 itemno INT REFERENCES Item(itemno),
 supplierno INT REFERENCES Supplier(supplierno),
 rate INT,
 PRIMARY KEY(itemno, supplierno)
);

//INSERT VALUES 

INSERT INTO Item VALUES
(1,'Pen',100),
(2,'Book',200);

INSERT INTO Supplier VALUES
(101,'ABC','Pune'),
(102,'XYZ','Mumbai');

INSERT INTO Item_Supplier VALUES
(1,101,500),
(1,102,700),
(2,101,900);

//TRIGGER

CREATE OR REPLACE FUNCTION check_rate()
RETURNS trigger AS $$
BEGIN
 IF ABS(NEW.rate - OLD.rate) > 2000 THEN
  RAISE EXCEPTION 'Rate difference greater than 2000 not allowed';
 END IF;

 RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_rate
BEFORE UPDATE ON Item_Supplier
FOR EACH ROW
EXECUTE FUNCTION check_rate();

//Q.2 - PROCEDURE DBMS 
CREATE OR REPLACE PROCEDURE calc(a INT, b INT)
AS $$
BEGIN
 RAISE NOTICE 'Addition: %', a+b;
 RAISE NOTICE 'Subtraction: %', a-b;
 RAISE NOTICE 'Multiplication: %', a*b;

 IF b != 0 THEN
  RAISE NOTICE 'Division: %', a/b;
 ELSE
  RAISE NOTICE 'Division not possible';
 END IF;
END;
$$ LANGUAGE plpgsql;