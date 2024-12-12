'''Visitor Pattern Python Version'''

class YQVisitor(): pass
class YQVisitee():
    def Accept(self, visitor : YQVisitor):
        Visit = getattr(visitor, f"Visit{self.__class__.__name__}")
        if callable(Visit): Visit(self) #double dispatch

class Student(YQVisitee): pass
class SeniorStudent(Student): pass
class PhDStudent(Student): pass
  
class SchoolInfomationSystem(YQVisitor):
    def VisitPhDStudent(self, sstudent : PhDStudent):
        print("A PhdStudent")

    def VisitSeniorStudent(self, sstudent : SeniorStudent):
        print("A SeniorStudent")

if "__main__" == __name__:
    print("Testing Visitor Pattern...")
    info_sys = SchoolInfomationSystem()
    phd_stu  = PhDStudent()
    sen_stu  = SeniorStudent()

    phd_stu.Accept(info_sys)
    sen_stu.Accept(info_sys)
