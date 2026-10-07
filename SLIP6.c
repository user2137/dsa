//SLIP - 6
//Q.1

#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node *left,*right;
};

struct node* create(int val){
    struct node* t=(struct node*)malloc(sizeof(struct node));
    t->data=val; t->left=t->right=NULL;
    return t;
}

struct node* insert(struct node* root,int val){
    if(root==NULL) return create(val);
    if(val<root->data)
        root->left=insert(root->left,val);
    else
        root->right=insert(root->right,val);
    return root;
}

// Copy BST
struct node* copy(struct node* root){
    if(root==NULL) return NULL;
    struct node* newNode=create(root->data);
    newNode->left=copy(root->left);
    newNode->right=copy(root->right);
    return newNode;
}

// Compare BST
int compare(struct node* r1, struct node* r2){
    if(r1==NULL && r2==NULL) return 1;
    if(r1==NULL || r2==NULL) return 0;

    return (r1->data==r2->data) &&
           compare(r1->left,r2->left) &&
           compare(r1->right,r2->right);
}

int main(){
    struct node *r1=NULL,*r2=NULL;
    int n,val;

    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d",&val);
        r1=insert(r1,val);
    }

    r2=copy(r1);

    if(compare(r1,r2))
        printf("Trees are equal\n");
    else
        printf("Not equal\n");

    return 0;
}

//Q.2 - DBMS
// DBMS
//CREATE TABLE 
CREATE TABLE BUS(
    bus_no INT PRIMARY KEY,
    capacity INT NOT NULL,
    depot_name VARCHAR(20)
);

CREATE TABLE DRIVER(
    driver_no INT PRIMARY KEY,
    driver_name CHAR(20),
    license_no INT UNIQUE,
    address CHAR(20),
    d_age INT,
    salary FLOAT
);

CREATE TABLE BUS_DRIVER(
    bus_no INT,
    driver_no INT,
    duty_date DATE,
    shift INT,
    PRIMARY KEY(bus_no,driver_no),
    FOREIGN KEY(bus_no) REFERENCES BUS(bus_no),
    FOREIGN KEY(driver_no) REFERENCES DRIVER(driver_no)
);

//INSERT VALUES 
INSERT INTO BUS VALUES
(1,50,'Pune'),
(2,40,'Nashik');

INSERT INTO DRIVER VALUES
(101,'Amit',111,'Pune',55,30000),
(102,'Rahul',112,'Nashik',45,25000);

INSERT INTO BUS_DRIVER VALUES
(1,101,'2024-01-01',1),
(2,102,'2024-01-02',2);

//FUNCTION
CREATE OR REPLACE FUNCTION get_driver(b_no INT)
RETURNS TEXT
LANGUAGE plpgsql
AS $$
DECLARE dname TEXT;
BEGIN
    SELECT driver_name INTO dname
    FROM DRIVER d, BUS_DRIVER bd
    WHERE d.driver_no=bd.driver_no
    AND bd.bus_no=b_no;

    RETURN dname;
END;
$$;

//Q.2 - PROCEDURE DBMS 
CREATE OR REPLACE PROCEDURE evenodd(n INT)
LANGUAGE plpgsql
AS $$
BEGIN
    IF n%2=0 THEN
        RAISE NOTICE 'Even';
    ELSE
        RAISE NOTICE 'Odd';
    END IF;
END;
$$;