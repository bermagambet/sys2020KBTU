#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/random.h>
#include <linux/kthread.h>
static int array[200000];
static int array2[200000];
static int array3[200000];
static int array4[200000];
static int array5[200000];

static int changer = 0;
static bool done = false;
#define TAG "Lab8"
#define MAX_NUM 1000000

int gen_int(void) {
    int n;
    get_random_bytes(&n, sizeof(n));
    n = n < 0 ? n * -1 : n;
    n = n % MAX_NUM;
    return n;
}

int sortByThread(void *unused) {
    int temp = 0;
    int i, j;
    for(i = 0; i < 1000000; i++) {
        if (i <= 199999 && changer == 0) {
            for(j = i + 1; j < 1000000; j++){
                if(j>199999 && j <= 399999){
                    if(array[i]>array2[j-200000]){
                        temp = array[i];
                        array[i] = array2[j-200000];
                        array2[j-200000] = temp;
                    }
                }
                else if (j > 399999 && j <=599999) {
                      if(array[i]>array3[j-400000]){
                        temp = array[i];
                        array[i] = array3[j-400000];
                        array3[j-400000] = temp;
                    }
                }
                else if (j > 599999 && j <=799999) {
                      if(array[i]>array4[j-600000]){
                        temp = array[i];
                        array[i] = array4[j-600000];
                        array4[j-600000] = temp;
                    }
                }
                else if (j  > 799999 && j <=999999) {
                      if(array[i]>array5[j-800000]){
                        temp = array[i];
                        array[i] = array5[j-800000];
                        array5[j-800000] = temp;
                    }
                }
                else 
                {
                      if(array[i]>array[j]){
                        temp = array[i];
                        array[i] = array[j];
                        array[j] = temp;
                    }
                }

            }
            if(i==199999){
                break;
            }
        }
        else if (i > 199999 && i <=399999 && changer == 1) {
            for(j = i + 1; j < 1000000; j++){
                if(j>199999 && j <= 399999){
                    if(array2[i-20000]>array2[j-200000]){
                        temp = array2[i-200000];
                        array2[i-200000] = array2[j-200000];
                        array2[j-200000] = temp;
                    }
                }
                else if (j > 399999 && j <=599999 && changer == 1) {
                      if(array2[i-200000]>array3[j-400000]){
                        temp = array2[i-200000];
                        array2[i-200000] = array3[j-400000];
                        array3[j-400000] = temp;
                    }
                }
                else if (j > 599999 && j <=799999 && changer == 1) {
                      if(array2[i-200000]>array4[j-600000]){
                        temp = array2[i-200000];
                        array2[i-200000] = array4[j-600000];
                        array4[j-600000] = temp;
                    }
                }
                else if (j  > 799999 && j <=999999 && changer == 1) {
                      if(array2[i-200000]>array5[j-800000]){
                        temp = array2[i-200000];
                        array2[i-200000] = array5[j-800000];
                        array5[j-800000] = temp;
                    }
                }

            }
        }
        else if (i > 399999 && i <=599999 && changer == 2) {
                for(j = i + 1; j < 1000000; j++){
                if (j > 399999 && j <=599999 && changer == 2 ){
                      if(array3[i-400000]>array3[j-400000]){
                        temp = array3[i-400000];
                        array3[i-400000] = array3[j-400000];
                        array3[j-400000] = temp;
                    }
                }
                else if (j > 599999 && j <=799999 && changer == 2) {
                      if(array3[i-400000]>array4[j-600000]){
                        temp = array3[i-400000];
                        array3[i-400000] = array4[j-600000];
                        array4[j-600000] = temp;
                    }
                }
                else if (j  > 799999 && j <=999999 && changer == 2) {
                      if(array3[i-400000]>array5[j-800000]){
                        temp = array3[i-400000];
                        array3[i-400000] = array5[j-800000];
                        array5[j-800000] = temp;
                    }
                }

            }
            if(i==599999){
                break;
            }
        }
        else if (i > 599999 && i <=799999 && changer == 2) {
            for(j = i + 1; j < 1000000; j++){
                if (j > 599999 && j <=799999 && changer == 2) {
                      if(array4[i-600000]>array4[j-600000]){
                        temp = array4[i-600000];
                        array4[i-600000] = array4[j-600000];
                        array4[j-600000] = temp;
                    }
                }
                else if (j  > 799999 && j <=999999 && changer == 2) {
                      if(array4[i-600000]>array5[j-800000]){
                        temp = array4[i-600000];
                        array4[i-600000] = array5[j-800000];
                        array5[j-800000] = temp;
                    }
                }

            }
        }
        else if (i > 799999 && i <=999999 && changer == 2) {
            for(j = i + 1; j < 1000000; j++){
                if (j  > 799999 && j <=999999 && changer == 2) {
                      if(array5[i-800000]>array5[j-800000]){
                        temp = array5[i-800000];
                        array5[i-800000] = array5[j-800000];
                        array5[j-800000] = temp;
                    }
                }

            }
            if(i==999999){
                done = true;
                break;
            }
        }
    }
   changer = (changer + 1) % 3;
   return 0; 
}

void initializeArrays(void) {
    int a, i;
    for(i = 0; i < 1000000;i++){
        a = gen_int();
        if(i<=199999){
            array[i] = a;
        }
        else if (i>199999 && i <= 399999) {
            array2[i-200000] = a;
        }
                else if (i>399999 && i <= 599999) {
            array3[i-400000] = a;
        }
                else if (i>599999 && i <= 799999) {
            array4[i-600000] = a;
        }
                else if (i>799999 && i <= 999999) {
            array5[i-800000] = a;
        }
    }
    
}

void createThreads(void) {
    int n; 
    n = gen_int();
    if (printk_ratelimit()) {
       printk(KERN_INFO "random number is %d\n", n);
    }
    struct task_struct *t1;
    struct task_struct *t2;
    struct task_struct *t3;

    int ok = 0;
    t1 = kthread_run(sortByThread, NULL, "mythread1");
    t2 = kthread_run(sortByThread, NULL, "mythread2");
    t3 = kthread_run(sortByThread, NULL, "mythread3");
}

int init_module(void)
{
        
        printk(KERN_INFO "START %s\n", TAG);
        initializeArrays();
        createThreads();
        printk(KERN_INFO "First 5 digits: %d, %d, %d, %d, %d", array[0], array[1], array[2], array[3], array[4]);

        printk(KERN_INFO "Last 5 digits: %d, %d, %d, %d, %d", array4[199995], array4[199996], array4[199997], array4[199998], array4[199999]);
        return 0;
}

void cleanup_module(void)
{       
        printk(KERN_INFO "First 5 digits: %d, %d, %d, %d, %d", array[0], array[1], array[2], array[3], array[4]);

        printk(KERN_INFO "Last 5 digits: %d, %d, %d, %d, %d", array4[199995], array4[199996], array4[199997], array4[199998], array4[199999]);
        printk(KERN_DEBUG "END %s\n", TAG);
}
