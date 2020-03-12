#include<iostream>

using namespace std;

class students{
    public:
        string get_student_name(void);
        int subject[100000];
        string student_name;
        double mean;
        void print_ans(int subject_num);
};

void students::print_ans(int subject_num){
    cout<<student_name<<":";
    for(int k = 0;k < subject_num;k++){
        cout<<subject[k]<<" ";
    }
    cout<<mean<<endl;

}


int main(void){
    int class_num,student_num,subject_num;
    double sum=0;
    cin>>class_num;

    for(int i = 0;i < class_num;i++){
        cin>>student_num>>subject_num;
        students student[student_num];
        for(int j = 0;j < student_num;j++){
            cin>>student[j].student_name;
            sum=0;
            for(int k = 0;k < subject_num;k++){
                cin>>student[j].subject[k];
                sum+=student[j].subject[k];
            }
            student[j].mean = sum/subject_num;
            for(int g=subject_num-1;g>0;g--){
                for(int l=0;l<g;l++){
                    if(student[j].subject[l]<student[j].subject[l+1])
                        swap(student[j].subject[l],student[j].subject[l+1]);
                }
            }
        }

        for(int g=student_num-1;g>0;g--){
            for(int l=0;l<g;l++){
                if(student[l].mean<student[l+1].mean)
                    swap(student[l],student[l+1]);
            }
        }
        for(int d=0;d<student_num;d++){
            student[d].print_ans(subject_num);
        }
        cout<<"=========="<<endl;
    }


    return 0;


}
