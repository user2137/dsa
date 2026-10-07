//SLIP - 28
//Q.1
#include<stdio.h>
#define SIZE 10

int table[SIZE];

void init(){
    for(int i=0;i<SIZE;i++)
        table[i] = -1;
}

void insert(int key){
    int i, index;

    for(i=0;i<SIZE;i++){
        index = (key + i*i) % SIZE;

        if(table[index] == -1){
            table[index] = key;
            printf("Inserted at %d\n", index);
            return;
        }
    }
    printf("Table Full\n");
}

void delete(int key){
    int i, index;

    for(i=0;i<SIZE;i++){
        index = (key + i*i) % SIZE;

        if(table[index] == key){
            table[index] = -1;
            printf("Deleted\n");
            return;
        }
    }
    printf("Not Found\n");
}

void display(){
    for(int i=0;i<SIZE;i++){
        printf("%d : %d\n", i, table[i]);
    }
}

int main(){
    int ch, key;

    init();

    do{
        printf("\n1.Insert\n2.Delete\n3.Display\n4.Exit\n");
        scanf("%d",&ch);

        switch(ch){
            case 1:
                printf("Enter key: ");
                scanf("%d",&key);
                insert(key);
                break;

            case 2:
                printf("Enter key: ");
                scanf("%d",&key);
                delete(key);
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

CREATE TABLE Company (
 name VARCHAR(30),
 address VARCHAR(50),
 city VARCHAR(20),
 share_value MONEY,
 PRIMARY KEY(name)
);

CREATE TABLE Person (
 pname VARCHAR(30),
 pcity VARCHAR(20),
 PRIMARY KEY(pname)
);

CREATE TABLE Company_Person (
 name VARCHAR(30) REFERENCES Company(name),
 pname VARCHAR(30) REFERENCES Person(pname),
 no_of_shares INT,
 PRIMARY KEY(name, pname)
);

//INSERT VALUES 

INSERT INTO Company VALUES
('TCS','Mumbai','Mumbai',1000),
('Infosys','Pune','Pune',2000);

INSERT INTO Person VALUES
('Om','Pune'),
('Amit','Mumbai');

INSERT INTO Company_Person VALUES
('TCS','Om',10),
('Infosys','Amit',20);

//TRIGGER

CREATE OR REPLACE FUNCTION prevent_delete()
RETURNS trigger AS $$
BEGIN
 RAISE NOTICE 'Company record cannot be deleted';
 RETURN NULL;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_comp
BEFORE DELETE ON Company
FOR EACH ROW
EXECUTE FUNCTION prevent_delete();

//Q.2 - PROCEDURE DBMS 
CREATE OR REPLACE PROCEDURE insert_person(pname VARCHAR, pcity VARCHAR)
AS $$
BEGIN
 INSERT INTO Person VALUES(pname, pcity);
 RAISE NOTICE 'Inserted Successfully';
END;
$$ LANGUAGE plpgsql;