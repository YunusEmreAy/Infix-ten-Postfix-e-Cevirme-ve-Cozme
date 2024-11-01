// Yunus Emre Ay / E-posta:TR.yunus.emre.ay@gmail.com

#include <stdio.h>
#include <stdlib.h>

struct stack
{
    char data;
    int puan;
    struct stack *next;
    struct stack *prev;

};

struct postfix
{
    char data;
    struct postfix *next;
};


struct stack *stack_start = NULL;
struct stack *s;
struct postfix *postfix_start = NULL;
struct postfix *p;
struct postfix *q;

int basamak[50]={0};

int kontrol(char islem[],int boyut)
{
    int i,a=0,k=0,sayac=0,s=0;

    for (i=0;i<boyut;i++)
    {
        if (islem[i]=='(')
        {
            a++;
        }
        else if (islem[i]==')')
        {
            k++;
        }
        if(k > a)
        {
            printf("Lutfen once acma parantezini girdiginizden emin olunuz. ");
            return 0;
        }
    }

    if (a==k)
    {
        for(i=0;i<boyut;i++)
        {
            if((islem[i]=='0')||(islem[i]=='1')||(islem[i]=='2')||(islem[i]=='3')||(islem[i]=='4')||
               (islem[i]=='5')||(islem[i]=='6')||(islem[i]=='7')||(islem[i]=='8')||(islem[i]=='9'))
            {
                sayac++;
            }
            else if(sayac != 0)
            {
                basamak[s] = sayac;
                s++;
                sayac = 0;
            }

        }
        if(sayac != 0)
        {
            basamak[s] = sayac;
            s++;
            sayac = 0;
        }

        return 1;
    }
    else
    {
        printf("Lutfen acma ve kapama parantezlerinin sayisinin esit oldugunu kontrol ediniz. ");
        return 0;
    }
}


void infix_postfix(char islem[],int boyut)
{

    int i,j,k,kontrol=0,stack_eleman,parantez_ac=0,parantez_kapat=0,space=20,a,stack_eleman2,b=1,psiz=0,c;


    for(i=0;i<boyut;i++)
    {
        if((islem[i]!='(')&&(islem[i]!=')'))
        {
            psiz++;
        }
    }

    for(i=0;i<boyut;i++)
    {
        if((islem[i]=='+')||(islem[i]=='-')||(islem[i]=='*')||(islem[i]=='/')||(islem[i]=='(')||(islem[i]==')'))
        {
            struct stack *yeni_eleman1 = (struct stack*)malloc(sizeof(struct stack));
            yeni_eleman1->data = islem[i];

            if(stack_start==NULL)
            {
                stack_start = yeni_eleman1;
                yeni_eleman1->next = NULL;
                yeni_eleman1->prev =NULL;
            }
            else
            {
                s = stack_start;
                while(s->next!=NULL)
                {
                    s = s->next;
                }
                s->next = yeni_eleman1;
                yeni_eleman1->next = NULL;
                yeni_eleman1->prev= s;
            }

            if((islem[i] == '+')||(islem[i] == '-'))
            {
                yeni_eleman1->puan = 1;
            }
            else if((islem[i] == '*')||(islem[i] == '/'))
            {
                yeni_eleman1->puan = 2;
            }
            else if((islem[i] == '(')||(islem[i] == ')'))
            {
                yeni_eleman1->puan = 0;
            }
        }
        else
        {
            struct postfix *yeni_eleman2 = (struct postfix*)malloc(sizeof(struct postfix));
            yeni_eleman2->data = islem[i];
            if(postfix_start==NULL)
            {
                postfix_start = yeni_eleman2;
                yeni_eleman2->next = NULL;
            }
            else
            {
                p = postfix_start;
                while(p->next!=NULL)
                {
                    p = p->next;
                }
                p->next = yeni_eleman2;
                yeni_eleman2->next = NULL;
            }

        }


        parantez_ac=0;
        parantez_kapat=0;

        if(stack_start != NULL)
        {
            s = stack_start;
            while(s->next!=NULL)
            {
                if (s->data == '(')
                {
                    parantez_ac++;
                }
                else if(s->data == ')')
                {
                    parantez_kapat++;
                }

                s = s->next;
            }
            if (s->data == '(')
            {
                parantez_ac++;
            }
            else if(s->data == ')')
            {
                parantez_kapat++;
            }
        }

        if ((parantez_ac>0) && (parantez_kapat>0))
        {
            s = stack_start;
            while(s->data != ')')
            {
                s = s->next;
            }
            while(s->prev->data != '(')
            {

                p = postfix_start;
                while(p->next!=NULL)
                {
                    p = p->next;
                }
                s = s->prev;
                p->next = s;
                p->next->next=NULL;

            }
            s = s->prev;
            if (s->prev!=NULL)
            {
                s = s->prev;
                s->next = NULL;
            }
            else
            {
                stack_start = NULL;
            }

        }


        stack_eleman = 0;
        if(stack_start!=NULL)
        {
            stack_eleman=1;
            s = stack_start;
            while(s->next!=NULL)
            {
                s = s->next;
                stack_eleman++;
            }
        }

        if(stack_eleman>=2)
        {
            s = stack_start;
            while(s->next != NULL)
            {
                s = s->next;

                while(((s->prev->puan != 0)&&(s->puan != 0))&&(s->puan <= s->prev->puan))
                {
                    p = postfix_start;
                    while(p->next != NULL)
                    {
                        p = p->next;
                    }

                    p->next = s->prev;
                    p->next->next = NULL;
                    s->prev = s->prev->prev;

                    if(s->prev != NULL)
                    {
                        s->prev->next = s;
                    }
                    else
                    {
                        stack_start = s;
                        break;
                    }
                }
            }
        }




        if(kontrol==0)
        {
            printf("\n\n\n\n\n   infix");
            for(a=0;a<space+boyut-6;a++)
            {
                printf(" ");
            }
            printf("Stack");
            for(a=0;a<space-6;a++)
            {
                printf(" ");
            }
            printf("Postfix\n");


            printf("\n");
            for(c=0;c<((space*2)+boyut+psiz+8);c++)
            {
                printf("-");
            }
            printf("\n");


            printf("%d)   ",b);
            b++;
            for(j=0;j<boyut-i;j++)
            {
                printf("%c",islem[i+j]);
            }
            kontrol=1;

            printf("\n");
            for(c=0;c<((space*2)+boyut+psiz+8);c++)
            {
                printf("-");
            }
            printf("\n");
        }



        printf("%d)  ",b);
        b++;

        if((b-1)<10)
        {
            printf(" ");
        }



        for(j=1;j<boyut-i;j++)
        {
            printf("%c",islem[i+j]);

        }


        for(a=0;a<space+i;a++)
        {
            printf(" ");
        }

        if(stack_start!=NULL)
        {
            s = stack_start;
            while(s->next!=NULL)
            {
                printf("%c",s->data);
                s = s->next;
            }
            printf("%c",s->data);
        }


        stack_eleman2 = 0;
        if(stack_start!=NULL)
        {
            stack_eleman2=1;
            s = stack_start;
            while(s->next!=NULL)
            {
                s = s->next;
                stack_eleman2++;
            }
        }

        for(a=0;a<space-stack_eleman2;a++)
        {
            printf(" ");
        }

        if(postfix_start!=NULL)
        {
            p = postfix_start;
            while(p->next!=NULL)
            {
                printf("%c",p->data);
                p = p->next;
            }
            printf("%c",p->data);
        }

        printf("\n");
        for(c=0;c<((space*2)+boyut+psiz+8);c++)
        {
            printf("-");
        }
        printf("\n");
    }



    if(stack_start!=NULL)
    {
        stack_eleman=1;
        s = stack_start;
        while(s->next!=NULL)
        {
            s = s->next;
            stack_eleman++;
        }
    }
    for(k=0;k<stack_eleman;k++)
    {
        s = stack_start;
        while(s->next!=NULL)
        {
            s = s->next;
        }

        p = postfix_start;
        while(p->next!=NULL)
        {
            p = p->next;
        }
        p->next = s;
        if(k!=stack_eleman-1)
        {
            s->prev->next= NULL;
        }
        else
        {
            stack_start = NULL;
        }
        s->prev= NULL;
    }



    printf("%d)  ",b);
    b++;

    if((b-1)<10)
    {
        printf(" ");
    }


    for(j=1;j<boyut-i;j++)
    {
        printf("%c",islem[i+j]);
    }


    for(a=0;a<space+i;a++)
    {
        printf(" ");
    }


    if(stack_start!=NULL)
    {
        s = stack_start;
        while(s->next!=NULL)
        {
            printf("%c",s->data);
            s = s->next;
        }
        printf("%c",s->data);
    }


    stack_eleman2 = 0;
    if(stack_start!=NULL)
    {
        stack_eleman2=1;
        s = stack_start;
        while(s->next!=NULL)
        {
            s = s->next;
            stack_eleman2++;
        }
    }

    for(a=0;a<space-stack_eleman2-1;a++)
    {
        printf(" ");
    }


    if(postfix_start!=NULL)
    {
        p = postfix_start;
        while(p->next!=NULL)
        {
            printf("%c",p->data);
            p = p->next;
        }
        printf("%c",p->data);
    }

    printf("\n");
    for(c=0;c<((space*2)+boyut+psiz+8);c++)
    {
        printf("-");
    }

}


void postfix_cozum(char islem[],int boyut)
{
    int b_kontrol=0,basamak_sayar=0,sayac=0,postfix_eleman=0,postfix_yazdirma=0,toplam=0;
    int i,b=1,j,gecici=0,psiz=0,stack_eleman=0,a;
    float sayilar[50]={0},tut=0.0;


    printf("\n\n\n\n\n");
    for(i=0;i<(postfix_eleman+boyut+48)*1.5;i++)
    {
        printf("x");
    }
    printf("\n\n\n\n\n");



    p = postfix_start;
    while(p->next!=NULL)
    {
        postfix_eleman++;
        p = p->next;
    }
    postfix_eleman++;

    printf("\n");
    for(i=0;i<postfix_eleman+boyut+48;i++)
    {
        printf("-");
    }
    printf("\n");

    printf("%d)   ",b);
    b++;
    for(i=0;i<boyut;i++)
    {
        printf("%c",islem[i]);
    }

    for(i=0;i<10;i++)
    {
        printf(" ");
    }
    printf("----->");
    for(i=0;i<10;i++)
    {
        printf(" ");
    }

    p = postfix_start;
    while(p->next!=NULL)
    {
        printf("%c",p->data);
        p = p->next;
    }
    printf("%c",p->data);


    printf("\n");
    for(i=0;i<postfix_eleman+boyut+48;i++)
    {
        printf("-");
    }
    printf("\n");


    printf("   Postfix");
    for(i=0;i<boyut+6;i++)
    {
        printf(" ");
    }

    printf("Stack");
    for(i=0;i<20;i++)
    {
        printf(" ");
    }

    printf("islem");

    printf("\n");
    for(i=0;i<postfix_eleman+boyut+48;i++)
    {
        printf("-");
    }
    printf("\n");


    printf("%d)   ",b);
    b++;

    p = postfix_start;
    while(p->next!=NULL)
    {
        printf("%c",p->data);
        p = p->next;
    }
    printf("%c",p->data);


    printf("\n");
    for(i=0;i<postfix_eleman+boyut+48;i++)
    {
        printf("-");
    }
    printf("\n");





    p = postfix_start;
    while (0==0)
    {
        while((p->data!='+')&&(p->data!='-')&&(p->data!='*')&&(p->data!='/'))
        {

            if((p->data=='0')||(p->data=='1')||(p->data=='2')||(p->data=='3')||(p->data=='4')||
               (p->data=='5')||(p->data=='6')||(p->data=='7')||(p->data=='8')||(p->data=='9'))
            {
                tut += p->data - '0';
                basamak_sayar++;
            }

            if(basamak[b_kontrol]==basamak_sayar)
            {
                basamak_sayar=0;
                break;
            }
            tut *= 10;
            p = p->next;

        }


        if((p->data!='+')&&(p->data!='-')&&(p->data!='*')&&(p->data!='/'))
        {

            for(j=0;j<50;j++)
            {
                if(sayilar[j]==0)
                {
                    break;
                }
            }

            sayilar[j] = tut;
            sayac++;
            b_kontrol++;
            tut=0;
        }



        toplam=0;
        for(j=0;j<sayac;j++)
        {
            toplam += basamak[j];
        }

        if((p->data=='+')||(p->data=='-')||(p->data=='*')||(p->data=='/'))
        {
            gecici++;
        }
        toplam += gecici;

        printf("%d)  ",b);
        b++;

        if((b-1)<10)
        {
            printf(" ");
        }

        q = postfix_start;
        postfix_yazdirma=0;
        while(q->next!=NULL)
        {
            if(postfix_yazdirma>=toplam)
            {
                printf("%c",q->data);
            }
            postfix_yazdirma++;
            q = q->next;
        }
        if(postfix_yazdirma>=toplam)
        {
            printf("%c",q->data);
        }

        for(j=0;j<toplam+15;j++)
        {
            printf(" ");
        }

        stack_eleman=0;
        for(j=0;sayilar[j]!=0;j++)
        {
            printf("%.2f ",sayilar[j]);

            a = sayilar[j];
            while(0==0)
            {
                if(a<=0)
                {
                    break;
                }
                a /= 10;
                stack_eleman++;
            }

        }
        stack_eleman = stack_eleman + (4*j);



        for(j=0;j<25-stack_eleman;j++)
        {
            printf(" ");
        }

        if(toplam>postfix_yazdirma)
        {
            break;
        }
        else if(sayac >= 2)
        {
            if((p->next->data=='+')||(p->next->data=='-')||(p->next->data=='*')||(p->next->data=='/'))
            {
                for(j=0;j<50;j++)
                {
                    if(sayilar[j]==0)
                    {
                        break;
                    }
                }
                if(p->next->data=='+')
                {
                    printf("%.2f+%.2f=%.2f",sayilar[j-2],sayilar[j-1],sayilar[j-2]+sayilar[j-1]);
                    sayilar[j-2] = sayilar[j-2] + sayilar[j-1];
                    sayilar[j-1] = 0.0;
                }
                else if(p->next->data=='-')
                {
                    printf("%.2f-%.2f=%.2f",sayilar[j-2],sayilar[j-1],sayilar[j-2]-sayilar[j-1]);
                    sayilar[j-2] = sayilar[j-2] - sayilar[j-1];
                    sayilar[j-1] = 0.0;
                }
                else if(p->next->data=='*')
                {
                    printf("%.2f*%.2f=%.2f",sayilar[j-2],sayilar[j-1],sayilar[j-2]*sayilar[j-1]);
                    sayilar[j-2] = sayilar[j-2] * sayilar[j-1];
                    sayilar[j-1] = 0.0;
                }
                else if(p->next->data=='/')
                {
                    printf("%.2f/%.2f=%.2f",sayilar[j-2],sayilar[j-1],sayilar[j-2]/sayilar[j-1]);
                    sayilar[j-2] = sayilar[j-2] / sayilar[j-1];
                    sayilar[j-1] = 0.0;
                }
            }
        }
        p = p->next;

        printf("\n");
        for(i=0;i<postfix_eleman+boyut+48;i++)
        {
            printf("-");
        }
        printf("\n");

    }

    printf("\n");
    for(i=0;i<postfix_eleman+boyut+48;i++)
    {
        printf("-");
    }
    printf("\n");

    printf("Sonuc: %.2f\n\n\n",sayilar[0]);

}



int main()
{
    int durum=0,boyut=0,i;
    char islem[100];
    while (durum==0)
    {
        printf("Lutfen yapmak istediginiz islemi giriniz -> ");
        scanf("%s",&islem);
        boyut = 0;
        for(i=0;i<100;i++)
        {
            if(islem[i]==NULL)
            {
                break;
            }
            boyut++;
        }
        durum = kontrol(islem,boyut);
    }



    infix_postfix(islem,boyut);

    postfix_cozum(islem,boyut);


    return 0;
}
