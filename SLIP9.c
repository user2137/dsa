//SLIP - 9
//Q.1

#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node* next;
};

struct node* table[10];

// Insert
void insert(int key){
    int h = key % 10;
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->data = key;
    temp->next = table[h];
    table[h] = temp;
}

// Search
void search(int key){
    int h = key % 10;
    struct node* p = table[h];

    while(p){
        if(p->data == key){
            printf("Element Found\n");
            return;
        }
        p = p->next;
    }
    printf("Element Not Found\n");
}

// Display
void display(){
    for(int i=0;i<10;i++){
        struct node* p = table[i];
        printf("%d: ", i);

        while(p){
            printf("%d -> ", p->data);
            p = p->next;
        }
        printf("NULL\n");
    }
}

int main(){
    int ch, key;

    // initialize
    for(int i=0;i<10;i++)
        table[i] = NULL;

    do{
        printf("\n1.Insert\n2.Search\n3.Display\n4.Exit\n");
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
                search(key);
                break;

            case 3:
                display();
                break;
        }
    }while(ch != 4);

    return 0;
}

//Q.2 - DBMS
// DBMS
//CREATE TABLE 
CREATE TABLE STUDENT (
 sreg_no INT PRIMARY KEY,
 name CHAR(30),
 class CHAR(10)
);

CREATE TABLE COMPETITION (
 c_no INT PRIMARY KEY,
 name CHAR(20),
 c_type CHAR(15)
);

-- M-M RELATION
CREATE TABLE STUDENT_COMPETITION (
 sreg_no INT REFERENCES STUDENT(sreg_no),
 c_no INT REFERENCES COMPETITION(c_no),
 rank INT,
 year INT,
 prize INT,
 PRIMARY KEY(sreg_no, c_no)
);

//INSERT VALUES 
INSERT INTO STUDENT VALUES
(1,'Om','SY'),
(2,'Amit','FY');

INSERT INTO COMPETITION VALUES
(101,'Quiz','Academic'),
(102,'Cricket','Sports');

INSERT INTO STUDENT_COMPETITION VALUES
(1,101,1,2020,5000),
(1,102,2,2020,2000),
(2,101,3,2021,1000);

//TRIGGER
CREATE OR REPLACE FUNCTION comp_update_msg()
RETURNS trigger AS $$
BEGIN
 RAISE NOTICE 'competition record is being updated';
 RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_comp_update
BEFORE UPDATE ON COMPETITION
FOR EACH ROW
EXECUTE FUNCTION comp_update_msg();

//Q.2 - PROCEDURE DBMS 
CREATE OR REPLACE PROCEDURE divide(a INT, b INT)
AS $$
BEGIN
 IF b = 0 THEN
  RAISE EXCEPTION 'Division by zero not allowed';
 ELSE
  RAISE NOTICE 'Division = %', a::NUMERIC / b;
 END IF;
END;
$$ LANGUAGE plpgsql;
