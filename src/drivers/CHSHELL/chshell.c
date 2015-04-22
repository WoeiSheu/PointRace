#include "chshell.h"

/*==================================================================================
	CH SHELL ��һ�����Ĵ�������������������ô��ڵ��ó������κεĲ��� V1.0
===================================================================================*/
//�Ա��ַ���
u8 CHS_StrCmp(u8*str1,u8 *str2)
{
	while(1)
	{
		if(*str1!=*str2)return 0;//�����
		if(*str1=='\0')break;//�Ա������.
		str1++;
		str2++;
	}
	return 1;//�����ַ������
}
//��str1������copy��str2  
void CHS_StrCopy(u8*SercStr,u8 *DestStr)
{
	while(1)
	{										   
		*DestStr=*SercStr;	//����
		if(*SercStr=='\0')break;//���������.
		SercStr++;
		DestStr++;
	}
}

void CHS_MemCopy(u8*Serc,u8 *Dest,u16 Num)
{
	while(Num--)
	{										   
		*Dest=*Serc;	//����
		Serc++;
		Dest++;
	}
}
//�õ��ַ����ĳ���(�ֽ�) 
u8 CHS_StrLen(u8*str)
{
	u8 len=0;
	while(1)
	{							 
		if(*str=='\0')break;//���������.
		len++;
		str++;
	}
	return len;
}
//����ֵ:m^n�η�
u32 CHS_Pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}	   
//����ַ���
u8 CHS_ClearStr(u8* str,u8 Num)
{
	while(Num--)
	{
		*str=' ';
		str++;
	}
	return 0;
}
//���ַ���תΪ����
//֧��16����ת��,����16������ĸ�����Ǵ�д��,�Ҹ�ʽΪ��0X��ͷ��.
//��֧�ָ��� 
//*str:�����ַ���ָ��
//*res:ת����Ľ����ŵ�ַ.
//����ֵ:0���ɹ�ת�����.����,�������.
//1,���ݸ�ʽ����.2,16����λ��Ϊ0.3,��ʼ��ʽ����.4,ʮ����λ��Ϊ0.
u8 CHS_Str2Num(u8*str,u32 *res)
{
	u32 t;
	u8 bnum=0;	 //���ֵ�λ��
	u8 *p;		  
	u8 hexdec=10;//Ĭ��Ϊʮ��������
	p=str;
	*res=0;//����.
	while(1)
	{
		if((*p<='9'&&*p>='0')||(*p<='F'&&*p>='A')||(*p=='X'&&bnum==1))//�����Ϸ�
		{
			if(*p>='A')hexdec=16;	//�ַ����д�����ĸ,Ϊ16���Ƹ�ʽ.
			bnum++;					//λ������.
		}else if(*p=='\0')break;	//����������,�˳�.
		else return 1;				//��ȫ��ʮ���ƻ���16��������.
		p++; 
	} 
	p=str;			    //���¶�λ���ַ�����ʼ�ĵ�ַ.
	if(hexdec==16)		//16��������
	{
		if(bnum<3)return 2;			//λ��С��3��ֱ���˳�.��Ϊ0X��ռ��2��,���0X���治������,������ݷǷ�.
		if(*p=='0' && (*(p+1)=='X'))//������'0X'��ͷ.
		{
			p+=2;	//ƫ�Ƶ�������ʼ��ַ.
			bnum-=2;//��ȥƫ����	 
		}else return 3;//��ʼͷ�ĸ�ʽ����
	}else if(bnum==0)return 4;//λ��Ϊ0��ֱ���˳�.	  
	while(1)
	{
		if(bnum)bnum--;
		if(*p<='9'&&*p>='0')t=*p-'0';	//�õ����ֵ�ֵ
		else t=*p-'A'+10;				//�õ�A~F��Ӧ��ֵ	    
		*res+=t*CHS_Pow(hexdec,bnum);		   
		p++;
		if(*p=='\0')break;//���ݶ�������.	
	}
	return 0;//�ɹ�ת��
}

//���Һ����Ĳ��� ���뺯���Ĳ����ַ���
//���� �����ĸ���
u8 CHS_GetParmNum(u8* str)
{
	u8 ParmNum=1;
	u8 IfStr=0;
	u8 ZeroParmTable1[]="()";
	u8 ZeroParmTable2[]="(void)";
	// 0�����ж�
	if(CHS_StrCmp(str,ZeroParmTable1) || CHS_StrCmp(str,ZeroParmTable2)) return 0;
	while(1)
	{
		if((*str==')'||*str=='\0')) break;
		if(*str==',' && IfStr==0) ParmNum++;
		if(*str=='"' && IfStr==1)
		{
			IfStr=0;
		}
		else if(*str=='"') IfStr=1;
		str++;
	}
	return ParmNum;
}

//����������Ϣ
//ֻ�����ڷ������ܵ�����������Ϣ ���ܷ�������
//���������Ϣ
u8 CHS_ParmProcess(u8* str,struct T_CHS_DEV* CHS_Dev)
{
	u8 i;
	u8 ParmPos[MAX_PARM];
	u8 Pos=0;
	u8 Temp[PARM_LEN];
	u32 NumParm;
	u8 Results;

	//��һ�� ��������������Buffer�е�λ��
	for(i=1;i<CHS_Dev->pnum+1;i++)
	{
		if(CHS_Dev->PInfo.Type[i]==2)
		{
			ParmPos[i]=Pos;
			Pos+=CHS_Dev->PInfo.Long[i]+2;//ֻ�洢�ַ���
		}
	}
  //��������
	for(i=1;i<CHS_Dev->pnum+1;i++)
	{
		if(CHS_Dev->PInfo.Type[i]==1) //����
		{
			CHS_StrCopy(str+CHS_Dev->PInfo.OffSet[i],Temp);
			Temp[CHS_Dev->PInfo.Long[i]]='\0';
			Results=CHS_Str2Num(Temp,&NumParm);
			if(Results!=0) return 1;
			CHS_Dev->PInfo.ParmData[i]=NumParm;
		}
		else //�ַ���
		{
			CHS_StrCopy(str+CHS_Dev->PInfo.OffSet[i],Temp);
			Temp[CHS_Dev->PInfo.Long[i]]='\0';
			CHS_StrCopy(Temp,CHS_Dev->PInfo.ParmBuf+ParmPos[i]);
			CHS_Dev->PInfo.ParmData[i]=(u32)&(CHS_Dev->PInfo.ParmBuf)+ParmPos[i];
		}
	}
	return 0;
}
//��ú��������ڲ����ַ����е�ƫ�ƺͳ���
u8 CHS_GetParmInfo(u8* str,struct T_CHS_DEV* CHS_Dev)
{
	u8 i=0;
	u8 j=0;
	u8 ParmNum=1;
	u8 IfStr=0;
	u8 len;
	u8* OrgStrPtr=str;
	//��ò�������
	CHS_Dev->PInfo.OffSet[1]=1;
	while(1)
	{
		if((*str==')'||*str=='\0')) break;
		if(*str==',' && IfStr==0)
		{
			ParmNum++;
			CHS_Dev->PInfo.OffSet[ParmNum]=i+1;
		}
		if((*str>='0' && *str<='9') && IfStr==0)
		{
			CHS_Dev->PInfo.Type[ParmNum]=1;
		}
		if(*str=='"' && IfStr==1)
		{
				IfStr=0;
		}
		else if(*str=='"')//����" ��ʼ����string
		{
			IfStr=1;
			CHS_Dev->PInfo.Type[ParmNum]=2; //ȷ�����ַ�������
		}
		str++;
		i++;
		
	}
	//�жϲ����Ŀ�ʼλ��
	for(i=1;i<ParmNum+1;i++)
	{
		if(CHS_Dev->PInfo.Type[i]==2)CHS_Dev->PInfo.OffSet[i]++;
	}
	//��ʼλ��Ѱ�ҽ���
	i=0;
	str=OrgStrPtr;       //��ԭ�ַ���
	len=CHS_StrLen(str); //����ַ�������
	//���ÿ�������ĳ���
	for(i=1;i<ParmNum+1;i++)
	{
		str=OrgStrPtr+CHS_Dev->PInfo.OffSet[i];
		for(j=CHS_Dev->PInfo.OffSet[i];j<len;j++)
		{
			if(CHS_Dev->PInfo.Type[i]==1)
			{
				if(*str==',' || *str=='"' || *str==')') //Ѱ�ҽ�����־
				{
					CHS_Dev->PInfo.Long[i]=j-CHS_Dev->PInfo.OffSet[i];
					break;	
				}
			}
			else
			{
				if(*str=='"')
				{
					CHS_Dev->PInfo.Long[i]=j-CHS_Dev->PInfo.OffSet[i]; //��¼������Ϣ
					break;	
				}
			}
			str++;
		}
	}
	return 0;
	//���������Σ�����Buffer�����
}
//����ַ����Ƿ�Ϸ� ���ҷ��뺯�����ַ����Ͳ����ַ���
//str     Դ�ַ���
//FunName ���������ַ���
//FunParm ���������ַ���
u8 CHS_StrCheck(u8* str,u8* FunName,u8* FunParm)
{
	u8 len;
	u8* StrStartPtr=str; //Դ�ַ���ָ��
	u8* p;
	u8 i=0;
	u8 FoverLeft=0;   //���ŵĸ���
	u8 FoverRight=0;  //���ŵĸ���
	u8 SpaceOffset=0; //��һ���ո�ǰ��ƫ��
	//�����ж�
	len=CHS_StrLen(str);
	if(len>(PARM_LEN+MAX_FNAME_LEN)) return 1;
	//�����ж�
	for(i=0;i<len;i++)
	{
		if(*str=='(')  FoverLeft++;
		if(*str==')')  FoverRight++;
		str++;
	}
	if(FoverLeft==0 || FoverRight==0 || FoverLeft!=FoverRight)  return 4;
	str=StrStartPtr; //��ԭ�ַ���ָ��
	
	for(i=0;i<len;i++)
	{
		if(*str=='(') break;
		str++;
	}
	FoverLeft=i;
	//������һ���ո񣬼���һ����ĸ�Ƿ�Ϊ�Ϸ���ĸ
	str=StrStartPtr;
	for(i=0;i<len;i++)
	{
		if(*str==' ' && (i<FoverLeft)) SpaceOffset=i+1;
		str++;
	}
	str=StrStartPtr;
	str=(str+SpaceOffset);
	p=str;
	if(!((*str>='a' && *str<='z')||(*str>='A' && *str<='Z')|| (*str=='_'))) return 5;
	//Ѱ�ҵ�һ��(
	str=StrStartPtr;
	for(i=0;i<len;i++)
	{
		if(*str=='(') break;
		str++;
	}
	str=p;
	CHS_MemCopy(str,FunName,i); //����FunName�ַ���
	CHS_StrCopy(str+i-SpaceOffset,FunParm);
	*(FunName+i-SpaceOffset)='\0';
	if(CHS_StrLen(FunName)>MAX_FNAME_LEN) return 6; //��ⳤ���Ƿ񳬳����
	if(CHS_StrLen(FunParm)>PARM_LEN)      return 6;
	return 0;
}
//�����
u8 *CHS_CMD_TABLE[]=
{
	"?",
	"help",
	"list",
};	
//��ִ�к���
u8  CHS_Scan()
{
	u8 i=0;
	u8 Result=0;
	u8 len=0;
	u8 LocalFunName[MAX_FNAME_LEN];   //���غ��������ַ���
	u8 LocalFunParm[PARM_LEN];        //���ز��������ַ���
	u8 RecFunName[MAX_FNAME_LEN];     //���յ��ĺ��������ַ���
	u8 RecFunParm[PARM_LEN];          //���յ��ĺ��������ַ���
	if((CHS_Dev.USART_STAT&0x8000)==0) return 1;
	len=CHS_Dev.USART_STAT&0x3fff;	 //�õ��˴ν��յ������ݳ���
	CHS_Dev.USART_BUF[len]='\0';	   //��ĩβ���������. 
	Result=CHS_StrCheck(CHS_Dev.USART_BUF,RecFunName,RecFunParm); //��������ַ����Ƿ�Ϊ������ʽ������ǣ��������ƺͲ����ַ���
	if(Result!=0) //����C���Ժ�����ʽ������
	{
		for(i=0;i<3;i++)//֧��3��ϵͳָ��
		{
			if(CHS_StrCmp(CHS_Dev.USART_BUF,CHS_CMD_TABLE[i]))break;
		}
		switch(i)
		{					   
			case 0:
			case 1://����ָ��
				printf("--------------------------CH SHELL V1.0------------------------ \r\n");
				printf("    CHSHELL����YANDLD������һ�����ɵĴ��ڵ��Ի������,ͨ����,�� \r\n");
				printf("����ͨ���������ֵ��ó���������κκ���,��ִ��.���,������������\r\n");
				printf("�������������.�����������֧��6���������.���������ֻ����ַ���  \r\n");	  
				printf("����֧��:www.tinychip.net\r\n");
				printf("CH SHELL��3��ϵͳ����:\r\n"); 
				printf("?:    ��ȡ������Ϣ\r\n");
				printf("help: ��ȡ������Ϣ\r\n");
				printf("list: ���õĺ����б�\r\n\n");
				printf("�밴�ճ����д��ʽ���뺯�������������Իس�������.\r\n");    
				printf("--------------------------YANDLD ------------------------- \r\n");
			case 2:
				printf("\r\n");
				printf("-------------------------�����嵥--------------------------- \r\n");
				for(i=0;i<CHS_Dev.fnum;i++)printf("%s\r\n",CHS_Dev.funs[i].name);
				printf("\r\n");
				return 0;
			default: 
				printf("�޷�ʶ���ָ��\r\n");
				return 1;
		}
	}
	  //��鱾���Ƿ��д˺���
		for(i=0;i<CHS_Dev.fnum;i++) 
		{
			Result=CHS_StrCheck((u8*)CHS_Dev.funs[i].name,LocalFunName,LocalFunParm);//�õ����غ���������������
			if(Result!=0)
			{
				printf("���غ����������� %d\r\n",Result);
				return 2;//���ؽ�������
			}
			if(CHS_StrCmp(LocalFunName,RecFunName))//���뺯�����ͱ��غ�����ƥ��
			{
				CHS_Dev.id=i;//��¼����ID.
				break;//����.
			}	
		}
		if(i==CHS_Dev.fnum) //���뺯�����ͱ��غ������޷�ƥ��
		{
			printf("�޷�ƥ�亯��\r\n");
			return 5;
		}
		//�����������Ƿ���ȷ
		if(CHS_GetParmNum(RecFunParm)!=CHS_GetParmNum(LocalFunParm))
		{
			printf("�������벻��ȷ ����%d ����%d\r\n",CHS_GetParmNum(LocalFunParm),CHS_GetParmNum(RecFunParm));
			return 6;
		}
		
		CHS_Dev.pnum=CHS_GetParmNum(RecFunParm); //��ȡ�˴�Ҫִ�к����Ĳ�������
		CHS_GetParmInfo(RecFunParm,&CHS_Dev);    //��ò�����Ϣƫ�ƺʹ�С
		CHS_ParmProcess(RecFunParm,&CHS_Dev);   //��������Ϣ
		//�����ȷ ��ʼ��������
		printf("\r\n%s(",RecFunName);//�����Ҫִ�еĺ�����
		for(i=1;i<CHS_Dev.pnum+1;i++) //����Ҫִ�еĲ���
		{
			if(CHS_Dev.PInfo.Type[i]==1) //����
			{
				printf("%d",CHS_Dev.PInfo.ParmData[i]);
			}
			else  //�ַ���
			{
				printf("%c",'"');			 
				printf("%s",(u8*)CHS_Dev.PInfo.ParmData[i]);
				printf("%c",'"');
			}
			if(i!=CHS_Dev.pnum)printf(",");
		}
		printf(")\r\n");	
		//��ʼִ��
		switch(CHS_Dev.pnum)
		{
			case 0://�޲���(void����)											  
				Result=(*(u32(*)())CHS_Dev.funs[CHS_Dev.id].func)();
				printf("FunRet: %d",Result);
				break;
	    case 1://��1������
				Result=(*(u32(*)())CHS_Dev.funs[CHS_Dev.id].func)(CHS_Dev.PInfo.ParmData[1]);
				printf("FunRet: %d",Result);
				break;
			case 2: //��2������
				Result=(*(u32(*)())CHS_Dev.funs[CHS_Dev.id].func)(CHS_Dev.PInfo.ParmData[1],CHS_Dev.PInfo.ParmData[2]);
				printf("FunRet: %d",Result);
				break;
			case 3: //��3������
				Result=(*(u32(*)())CHS_Dev.funs[CHS_Dev.id].func)(CHS_Dev.PInfo.ParmData[1],CHS_Dev.PInfo.ParmData[2],CHS_Dev.PInfo.ParmData[3]);
				printf("FunRet: %d",Result);
				break;
			case 4: //��4������
				Result=(*(u32(*)())CHS_Dev.funs[CHS_Dev.id].func)(CHS_Dev.PInfo.ParmData[1],CHS_Dev.PInfo.ParmData[2],CHS_Dev.PInfo.ParmData[3],CHS_Dev.PInfo.ParmData[4]);
				printf("FunRet: %d",Result);
				break;		
			case 5: //��5������
				Result=(*(u32(*)())CHS_Dev.funs[CHS_Dev.id].func)(CHS_Dev.PInfo.ParmData[1],CHS_Dev.PInfo.ParmData[2],CHS_Dev.PInfo.ParmData[3],CHS_Dev.PInfo.ParmData[4],\
				CHS_Dev.PInfo.ParmData[5]);
				printf("FunRet: %d",Result);
				break;		
			case 6: //��6������
				Result=(*(u32(*)())CHS_Dev.funs[CHS_Dev.id].func)(CHS_Dev.PInfo.ParmData[1],CHS_Dev.PInfo.ParmData[2],CHS_Dev.PInfo.ParmData[3],CHS_Dev.PInfo.ParmData[4],\
				CHS_Dev.PInfo.ParmData[5],CHS_Dev.PInfo.ParmData[6]);
				printf("FunRet: %d",Result);
				break;	
			default :
				printf("�������\r\n");
				break;
		}
		return 0;
}

//����1���ַ��� ������ճɹ�������scan() ����һ��
void CHS_Rev1(u8 ch)
{
	if((CHS_Dev.USART_STAT&0x8000)==0)
	{
		if(CHS_Dev.USART_STAT&0x4000) //���յ���0x0D
		{
			if(ch!=0x0A)  CHS_Dev.USART_STAT=0; //���մ���
			else  
			{
				CHS_Dev.USART_STAT|=0x8000;    //�������
				CHS_Scan();                    //ִ��������
				CHS_ClearStr(CHS_Dev.USART_BUF,sizeof(CHS_Dev.USART_BUF));
				CHS_Dev.USART_STAT=0;
			}
		}
		else 
		{
			if(ch==0x0d) CHS_Dev.USART_STAT|=0x4000;//���յ��˻س���
			else
			{
				CHS_Dev.USART_BUF[CHS_Dev.USART_STAT&0x3FFF]=ch;
				CHS_Dev.USART_STAT++;
				if((CHS_Dev.USART_STAT&0x3FFF)>(MAX_FNAME_LEN+PARM_LEN-1)) CHS_Dev.USART_STAT=0; //�������ݴ���,���¿�ʼ����	  
			}		
		}
	}
}

