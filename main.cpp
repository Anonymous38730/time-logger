#include <cstdio>
#include "stringc.h"
#include "timec.h"
#include "log.h"

int main() {
    /*/ // String
    printf("Демонстрация String:\n");

    String S1;
    String S2 = "test";
    String S3 = S2;
    printf("S1: Без параметров: \t\"%s\"\n", S1.getText());
    printf("S2: S2 = \"test\": \t\"%s\"\n", S2.getText());
    printf("S3: Копия S2: \t\"%s\"\n", S3.getText());
    S1 <<= S2;
    printf("S1 <<= S2: \t\"%s\"\n", S1.getText());
    S1 <<= " ";
    printf("S1 <<= \" \": \t\"%s\"\n", S1.getText());
    printf("(S1 << S3): \t\"%s\"\n", (S1 << S3).getText());
    printf("(S1 << \"тест\"): \t\"%s\"\n", (S1 << "тест").getText());
    S1 <<= S1;
    printf("S1 <<= S1: \t\"%s\"\n", S1.getText());
    S1 <<= (S1 << S1);
    printf("S1 <<= (S1 << S1): \t\"%s\"\n", S1.getText());

    printf("\n-----\n\n");
    //*/

    //*/ // Time
    printf("Демонстрация Time:\n");

    Time t1;
    Time t2(1,2,30,635);
    Time t3 = t2;
    printf("t1: Без параметров: \t%s\n", t1.toString().getText());
    printf("t2: С параметрами: \t%s\n", t2.toString().getText());
    printf("t2.getH/M/S/MS(): \t%d, %d, %d, %d\n",
        t2.getH(), t2.getM(), t2.getS(), t2.getMS()
    );
    printf("t3: Копия 2: \t%s\n", t3.toString().getText());
    t1 = t3;
    printf("t1 = t3: \t%s\n", t1.toString().getText());
    t3.set(9,8,7,6);
    printf("t3.set(h,m,s,ms): \t%s\n", t3.toString().getText());
    printf("Time::getCurrentTime(): \t%s\n",
        Time::getCurrentTime().toString().getText()
    );
    t3 += t2;
    printf("t3 += t2: \t%s\n", t3.toString().getText());
    t3 -= t2;
    printf("t3 -= t2: \t%s\n", t3.toString().getText());
    printf("(t3 + t2): \t%s\n", (t3 + t2).toString().getText());
    printf("(t3 - t2): \t%s\n", (t3 - t2).toString().getText());
    t3.addMS(1234);
    printf("t3.addMS(ms): \t%s\n", t3.toString().getText());
    t3.subtractMS(1234);
    printf("t3.subtractMS(ms): \t%s\n", t3.toString().getText());
    printf("t3.compare(t2): \t%d\n", t3.compare(t2));
    printf("t2.compare(t3): \t%d\n", t2.compare(t3));
    printf("t2.compare(t2): \t%d\n", t2.compare(t2));

    printf("\n-----\n\n");
    //*/

    //*/ // Log
    printf("Демонстрация Log:\n");

    int d;
    Log L1;
    L1
        .info("L1.info(char *s, Time t)", Time(2))
        .info(String("L1.info(String S, Time t)"), Time(3))
        .error("L1.error(char *s, Time t)", Time(1))
        .error(String("L1.error(String S, Time t)"), Time(4))
    ;
    printf("Активация искусственной задержки (ввод цифр)\n");
    scanf("%d", &d);
    L1.info("L1.info(char *s)");
    scanf("%d", &d);
    L1.info(String("L1.info(String S)"));
    Time LT1 = Time::getCurrentTime();
    scanf("%d", &d);
    L1.error("L1.error(char *s)");
    scanf("%d", &d);
    L1.error(String("L1.error(String S)"));
    
    Log La("Log La(char *s)");
    Log Lb(String("Log Lb(String S)"));
    Log Lc("Log Lc(char *s, Time t)", Time(999,999,999,999));
    Log Ld(String("Log Ld(String S, Time t)"), Time(999,999,999,999));
    printf("Конструкторы с параметрами:\n%s%s%s%s\n",
        La.toString().getText(),
        Lb.toString().getText(),
        Lc.toString().getText(),
        Ld.toString().getText()
    );
    printf("L1:\n%s\n", L1.toString().getText());
    Log L2 = L1;
    printf("L2: копия L1:\n%s\n", L2.toString().getText());
    Log L3;
    printf("L3: пустой лог:\n%s\n", L3.toString().getText());
    L3 = L2;
    printf("L3 = L2:\n%s\n", L3.toString().getText());
    L3.clear();
    printf("Очистка лога: \n%s\n", L3.toString().getText());
    printf("Срез сверху по количеству:\n%s\n", L1.head(3).toString().getText());
    printf("Срез снизу по количеству:\n%s\n", L1.tail(3).toString().getText());
    printf("Срез сверху по времени:\n%s\n", L1.head(LT1).toString().getText());
    printf("Срез снизу по времени:\n%s\n", L1.tail(LT1).toString().getText());

    //*/
    
    return 0;
}
