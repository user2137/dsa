//SLIP - 15
//Q.1
#include<stdio.h>

int table[10];

// Insert using quadratic probing
void insert(int key){
    int h = key % 10;
    int i = 0;

    while(table[(h + i*i) % 10] != 0){
        i++;
    }

    table[(h + i*i) % 10] = key;
}

// Search
void search(int key){
    int h = key % 10;
    int i = 0;

    while(table[(h + i*i) % 10] != 0){
        if(table[(h + i*i) % 10] == key){
            printf("Found\n");
            return;
        }
        i++;
    }
    printf("Not Found\n");
}

// Display
void display(){
    for(int i=0;i<10;i++){
        printf("%d ",table[i]);
    }
}

// Main
int main(){
    int ch,key;

    for(int i=0;i<10;i++)
        table[i]=0;

    do{
        printf("\n1.Insert\n2.Search\n3.Display\n4.Exit\n");
        scanf("%d",&ch);

        switch(ch){
            case 1:
                scanf("%d",&key);
                insert(key);
                break;
            case 2:
                scanf("%d",&key);
                search(key);
                break;
            case 3:
                display();
                break;
        }
    }while(ch!=4);

    return 0;
}

//Q.2 - DBMS
// DBMS
//CREATE TABLE 
CREATE TABLE Area(
    aname VARCHAR(20) PRIMARY KEY,
    area_type VARCHAR(5) CHECK(area_type IN ('urban','rural'))
);

CREATE TABLE Person(
    pnumber INT PRIMARY KEY,
    pname VARCHAR(20),
    birthdate DATE,
    income INT,
    aname VARCHAR(20),
    FOREIGN KEY(aname) REFERENCES Area(aname)
);

//INSERT VALUES 
INSERT INTO Area VALUES
('Pune','urban'),
('Nashik','urban'),
('Village','rural');

INSERT INTO Person VALUES
(1,'Amit','2000-01-01',50000,'Pune'),
(2,'Rahul','1999-02-02',30000,'Nashik'),
(3,'Sita','2001-03-03',20000,'Village');

//TRIGGER
CREATE OR REPLACE FUNCTION check_person()
RETURNS trigger AS $$
BEGIN
 IF NEW.pnumber < 0 THEN
  RAISE EXCEPTION 'Invalid Number';
 END IF;

 RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_person
BEFORE INSERT ON Person
FOR EACH ROW
EXECUTE FUNCTION check_person();

//Q.2 - PROCEDURE DBMS 
CREATE OR REPLACE PROCEDURE odd_numbers()
AS $$
DECLARE
 i INT := 1;
BEGIN
 WHILE i <= 100 LOOP
  IF i % 2 != 0 THEN
   RAISE NOTICE '%', i;
  END IF;
  i := i + 1;
 END LOOP;
END;
$$ LANGUAGE plpgsql;
