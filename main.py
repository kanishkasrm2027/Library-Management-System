import pickle
def create():
    n=int(input("Enter the number of books for which details to be created:"))
    f=open("text2.doc", "ab+")
    for i in range(n):
        dict_fields={}
        print("Enter the details of the book {}:".format(i+1))
        dict_fields['Bookid']=int(input("Enter the book's id:"))
        dict_fields['Bookname']=str(input("Enter the book's name:"))
        dict_fields['Quantity']=int(input("Enter the number of books available:"))
        dict_fields['Category']=str(input("Enter the category of the book:"))  
        dict_fields['Author']=str(input("Enter the author of the book:"))
        pickle.dump(dict_fields,f)
    print("Book details created")
    f.close()
def update():
    f=open("text2.doc",'rb+')
    print("You can update only the number of books available")
    print("Do you want to see the existing book details?----Yes/No")
    print("If YES is your choice you will be redirected to book menu and choose update again and give your choice as NO")
    choice=str(input("Enter your choice:"))
    if choice=='yes' or choice=='Yes':
        objects=[]
        while True:
            try:
                data=pickle.load(f)
                objects.append(data)
            except EOFError:
                break
        for obj in objects:
            print(obj)
    if choice=='no' or choice=='No':
        id=int(input("Enter the id of the book for which you want to update the quantity:"))
        objects=[]
        while True:
            try:
                data=pickle.load(f)
                objects.append(data)
            except EOFError:
                break
        for obj in objects:
            if obj['Bookid']==id:
                quantity=int(input("Enter the number of books available now:"))
                obj['Quantity']=quantity
                print(obj)
            else:
                pass
        f.close()
def search():
    f=open("text2.doc",'rb')
    objects=[]
    while True:
        try:
            data=pickle.load(f)
            objects.append(data)
        except EOFError:
            break
    print("Fields of the book details are: 1.Book id 2.Name 3.Category 4.Author's Name")
    print("Using which field you want to search the book details?")
    choice=int(input("Enter your choice:"))
    if choice==1:
        id=int(input("Enter the required book's id:"))
        for book in objects:
            if book['Bookid']==id:
                print("The details of the book whose id is {} are:".format(id),book)
    elif choice==2:
        name=input("Enter the required book's name:")
        for book in objects:
            if book['Bookname']==name:
                print("The details of the book whose name is {} are:".format(name),book)
    elif choice==3:
        cat=str(input("Enter the required book's category:"))
        for book in objects:
            list1=[]
            if book['Category']==cat:
                list1.append(book)
                for i in range(len(list1)):
                    print("The details of the book whose category is {} are:".format(cat),list1[i])
    elif choice==4:
        author=str(input("Enter the required book's author name:"))
        for book in objects:
            list2=[]
            if book['Author']==author:
                list2.append(book)
                for i in range(len(list2)):
                    print("The details of the book whose author is {} are:".format(author),list2[i])
    else:
        pass
    f.close()
def delete():
    f=open("text2.doc",'rb')
    objects=[]
    while True:
        try:
            data=pickle.load(f)
            objects.append(data)
        except EOFError:
            break
    id=int(input("Enter the id of the book whose details to be deleted:"))
    for book in objects:
        if book['Bookid']==id:
            del book 
            print("The book details with id {} is deleted.".format(id))
        else:
            break

def create_student():
    n=int(input("Enter the number of students to create their details:"))
    f=open("text3.doc", "ab+")
    for i in range(n):
        student_details={}
        print("Enter the details of the student {}:".format(i+1))
        student_details['Student id']=int(input("Enter the student's id:"))
        student_details['Student Name']=str(input("Enter the student's name:"))
        student_details['Book\'s Name']=str(input("Enter the name of the book/books:"))
        student_details['Book taken on']=str(input("Enter the date the book was taken:"))  
        student_details['Book returned on']=str(input("Enter the date the book was returned:")) 
        pickle.dump(student_details,f)
    print("Student details created")
    f.close()
def update_student():
    f=open("text3.doc",'rb+')
    objects=[]
    while True:
        try:
            data=pickle.load(f)
            objects.append(data)
        except EOFError:
            break
    stu_id=int(input("Enter the student's id whose details you want to update:"))
    for book in objects:
        if book['Student id']==stu_id:
            return_date=input("Enter the date the book was returned by the student:")
            book['Book returned on']=return_date
            print(book)
        else:
            pass
    f.close()
def delete_student():
    f=open("text3.doc",'rb')
    objects=[]
    while True:
        try:
            data=pickle.load(f)
            objects.append(data)
        except EOFError:
            break
    id=int(input("Enter the id of the student whose details to be deleted:"))
    for book in objects:
        if book['Student id']==id:
            del book 
            print("The student details with id {} is deleted.".format(id))
        else:
            print("A student with id {} doesn't exist".format(id))
def search_student():
    f=open("text3.doc",'rb')
    objects=[]
    while True:
        try:
            data=pickle.load(f)
            objects.append(data)
        except EOFError:
            break
    print("Fields of the student details are: 1.Student id 2.Student Name 3.Book's Name")
    print("Using which field you want to search the book details?")
    choice=int(input("Enter your choice:"))
    if choice==1:
        id=int(input("Enter the required student's id:"))
        for book in objects:
            if book['Student id']==id:
                print("The details of the student whose id is {} are:".format(id),book)
    elif choice==2:
        name=input("Enter the required student's name:")
        for book in objects:
            if book['Student Name']==name:
                print("The details of the student whose name is {} are:".format(name),book)
    elif choice==3:
        Book_name=str(input("Enter the book\'s name which was taken by the student:"))
        for book in objects:
            list2=[]
            if book['Book\'s Name']==Book_name:
                list2.append(book)
                for i in range(len(list2)):
                    print("The details of the student who took the book {} are:".format(Book_name),list2[i])
    else:
        pass
    f.close()
def book():
    print("Choose from the following options:")
    print("1.Add a new book")
    print("2.Delete an existing book")
    print("3.Search for a book")
    print("4.Update the book details")
    print("5.Exit")
    ch=int(input("Enter your option:"))
    if ch==1:
        create()
        print("CHANGES ON BOOK DETAILS IS MADE SUCCESSFULLY")
        book()
    elif ch==2:
        delete()
        print("CHANGES ON BOOK DETAILS IS MADE SUCCESSFULLY")
        book()
    elif ch==3:
        search()
        book()
    elif ch==4:
        update()
        print("CHANGES ON BOOK DETAILS IS MADE SUCCESSFULLY")
        book()
    elif ch==5:
        main()
    else:
        pass
def student():
    print("Choose from the following options: ")
    print("1.Add a new student.")
    print("2.Delete an existing student.")
    print("3.Search for a student.")
    print("4.Update a student\'s details")
    print("5.Exit.")        
    ch=int(input("Enter your option:"))
    if ch==1:
        create_student()
        print("CHANGES ON STUDENT DETAILS IS MADE SUCCESSFULLY")
        student()
    elif ch==2:
        delete_student()
        print("CHANGES ON STUDENT DETAILS IS MADE SUCCESSFULLY")
        student()
    elif ch==3:
        search_student()
        student()
    elif ch==4:
        update_student()
        print("CHANGES ON STUDENT DETAILS IS MADE SUCCESSFULLY")
        student()
    elif ch==5:
        main()
    else:
        pass

def main():
    print("\n\nWelcome to the library management system.")
    print("Please choose from one of the following options: ")
    print("1.BOOK DETAILS")
    print("2.STUDENT DETAILS")
    print("3.EXIT")
    choice=int(input("Enter your option:"))
    if choice==1:
        book()
    if choice==2:
        student()
    if choice==3:
        exit()
main()


