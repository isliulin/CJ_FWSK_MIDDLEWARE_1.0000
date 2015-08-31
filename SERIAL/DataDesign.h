#ifndef DATA_DESIGN
#define DATA_DESIGN

#define INV_MAX_NUM 100

//-----------------------------------------------------------------
//����ͨ�����ݳ��ȶ���
//-----------------------------------------------------------------
#define JQBH_LEN			12				//������ų���
#define KOULING_LEN			8				//�豸�����

#define ZSKOULING_LEN		8				//֤������
#define SBBH_LEN			12				//�豸��ų���
#define NSRSBH_LEN			20				//��˰��ʶ��ų���
#define FKDWSH_LEN			20				//���λ˰�ų���
#define NSRMC_LEN			80				//��˰�����Ƴ���
#define SKDWMC_LEN			80				//�տλ���Ƴ���
#define FKDWMC_LEN			80				//���λ���Ƴ���
#define SWJGDM_LEN			11				//˰����ش��볤��
#define SWJGMC_LEN			80				//˰��������Ƴ���
#define FPLXDM_A_LEN		30				//��Ʊ���ʹ������ݳ���
#define SZSJ_LEN			14				//ʱ��ʱ�䳤��
#define BBH_LEN				10				//�汾�ų���
#define KPJH_LEN			5				//��Ʊ���ų���
#define QYLX_LEN			3				//��ҵ���ͳ���
#define BLXX_LEN			16				//������Ϣ����
#define KZXX_LEN			80				//��չ��Ϣ����
#define SPHSL_LEN			4				//��Ʒ����������

#define FPLXDM_S_LEN		3				//������Ʊ���ʹ��볤��
#define DATE_LEN			8				//���ڳ���
#define TIME_LEN			6				//ʱ�䳤��
#define XIANE_LEN			12				//�޶����ݳ���
#define FSFPTS_LEN			4				//���߸�����Ʊ�޶���������
#define SYRL_LEN			12				//ʣ����������
#define SCJZRQ_LEN			2				//�ϴ���ֹ���ڳ���
#define LXXDGNBS_LEN		4				//�����޶����ܱ�ʶ����
#define LXKPSC_LEN			5				//���߿�Ʊ�޶�ʱ������
#define LXKPZS_LEN			10				//���߿�Ʊ��������
#define LXKZXX_LEN			160             //���߿�Ʊ��չ��Ϣ����
#define ZDYXX_LEN			100				//�Զ�����Ϣ����

#define SZSMSYH_LEN			3				//˰��˰Ŀ�����ų���
#define SZSMDM_LEN			6				//˰��˰Ŀ���볤��
#define TAXRATE_LEN			6				//˰�ʳ���
#define SZSMMC_LEN			40				//˰��˰Ŀ���Ƴ���

#define FPDM_LEN			12				//��Ʊ���볤��
#define FPHM_LEN			8				//��Ʊ���볤��
#define FPFS_LEN			12				//��Ʊ��������
#define FPZS_LEN			10				//��Ʊ��������
#define RYMC_LEN			20				//��Ա���Ƴ���
#define FPJFS_LEN			3				//��Ʊ�����������
#define QTXX_LEN			500				//������Ϣ
#define HZXX_LEN			100				//������Ϣ
#define ZH_QTXX_LEN			50				//˰���豸��˰����ϲ�����������Ϣ

#define ITEM_MAX_COUNT		10				//����Ʊ�����Ŀ����
#define FPLG_MAX_COUNT		10				//��Ʊ�칺������

#define HYFL_LEN			20				//��ҵ���೤��
#define XMMC_LEN			20				//��Ŀ���Ƴ���
#define DJ_LEN				12				//���۳���
#define SL_LEN				12				//��������
#define JE_LEN				12				//����
#define TAXRATE_NUM_LEN		3				//˰����������
#define TAXRATE_MAX_NUM		10				//˰��������
#define TAX_LEN				12				//˰���
#define BZ_LEN				80				//��ע����
#define SKM_SHORT_LEN		20				//��˰���볤��
#define SKM_LONG_LEN		190				//��˰���볤��
#define SIGN_LEN			512				//ǩ������

#define CXTJ_LEN			30				//��ѯ��������
#define FPFS_LEN			12				//��Ʊ��������
#define ITEM_COUNT_LEN		3				//����Ŀ��������

#define KPLX_ZSFP			0				//������Ʊ����
#define KPLX_FSFP			1				//������Ʊ����
#define WASTE_KBFP			0				//�հ׷�Ʊ��������
#define WASTE_YKFP			1				//�ѿ���Ʊ��������

#define	IFDTIP_LEN			1				//�Ƿ��Զ�����IP����
#define	FFBZ_LEN			2				//�ַ���־����

#define	IP_LEN			    20				//IP����
#define	GATE_LEN			20				//���س���
#define	MASK_LEN			20				//�������볤��
#define	DNS_LEN				20				//DNS����
#define	PORT_LEN			6				//�˿ںų���
#define	FWQBSLJ_LEN			50				//����������·������
#define	USERNAME_LEN		16				//�û�������
#define	PASSWORD_LEN		16				//���볤��

#define	WSCFPZS_LEN			8				//δ�ϴ���Ʊ����
#define	SCZS_LEN			5				//�ϴ�����
#define	SCSJJG_LEN			10				//�ϴ�ʱ����
#define CWMS_LEN			128				//��������

//-----------------------------------------------------------------
//����ͨ�������ֶ���
//-----------------------------------------------------------------
#define SERIAL_ONLINE_CMD			0x01		//��������
#define SERIAL_SKPBHCX_CMD			0x02		//˰���̱�Ų�ѯ����
#define SERIAL_BSPBHCX_CMD			0x03		//��˰�̱�Ų�ѯ����
#define SERIAL_SKPXXCX_CMD			0x04		//˰������Ϣ��ѯ����
#define SERIAL_BSPXXCX_CMD			0x05		//��˰����Ϣ��ѯ����
#define SERIAL_JKSJCX_CMD			0x06		//������ݲ�ѯ����
#define SERIAL_SQSLCX_CMD			0x07		//��Ȩ˰�ʲ�ѯ����
#define SERIAL_GPXXCX_CMD			0x08		//��Ʊ��Ϣ��ѯ����
#define SERIAL_SKSBKLGG_CMD			0x09		//�����������
#define SERIAL_FPKJ_CMD				0x0A		//��Ʊ��������
#define SERIAL_FPZF_CMD				0x0B		//��Ʊ��������
#define SERIAL_FPCX_CMD				0x0C		//��Ʊ��ѯ����
#define SERIAL_SKPBSPZHCZ_CMD		0x0D		//˰���̱�˰����ϲ�������
#define SERIAL_BSPFPCX_CMD			0x0E		//��˰�̷�Ʊ��ѯ����
#define SERIAL_FPFF_CMD				0x0F		//��Ʊ�ַ�����
#define SERIAL_FPHS_CMD				0x10		//��Ʊ��������
#define SERIAL_SJCB_CMD				0x11		//���ݳ�������
#define SERIAL_WLJKHC_CMD			0x12		//�����ػش�����
#define SERIAL_FPTJXXCX_CMD			0x13		//��Ʊͳ����Ϣ��ѯ����
#define SERIAL_QYXXGX_CMD			0x14		//��ҵ��Ϣ��������
#define SERIAL_LXQXGX_CMD			0x15		//����Ȩ�޸�������
#define SERIAL_FPSSSC_CMD			0x16		//��Ʊʵʱ�ϴ�����
#define SERIAL_WLCSWH_CMD			0x17		//�������ά������
#define SERIAL_SZCKBTL_CMD			0x18		//���ô��ڲ���������
#define SERIAL_FPDR_CMD				0x19		//��Ʊ��������
#define SERIAL_FJTH_CMD				0x1A		//�ֻ��˻�����
#define SERIAL_WLGP_CMD				0x1B		//���繺Ʊ����
#define SERIAL_ZSKLGG_CMD			0x1C		//֤������������
#define SERIAL_FPBL_CMD				0x1D		//��Ʊ��¼����
#define SERIAL_HQLXSJ_CMD			0x30		//��ȡ������������

#define SERIAL_ERRUPINV_CMD			0x31		//��ȡ�ϴ�����Ʊ��Ϣ
#define SERIAL_CONNECT_TEST_CMD		0x32		//��ȫͨ�����Ӳ���
#define SERIAL_ZHQQK_CMD			0x99		//ת�������

#define SERIAL_YYSJ_CMD				0xFE		//Ӧ����������
#define SERIAL_SYSTEST_CMD			0xFD		//ϵͳ�Լ�����
#define SERIAL_WMAC_CMD				0xFC		//��дMAC����
#define SERIAL_WJQBH_CMD			0xFB		//��д�����������


//     weichao
#define SQL_CMD "../sqlite3 LIBAWE < ../libawe.sql"     //�ؽ����ݿ�����
#define RMLIB_CMD "rm -rf LIBAWE"                     //ɾ�����ݿ��ļ�����
#define REBOOT_CMD "reboot -f"                        //����
#define MOUNT_CMD "mount /dev/sda1 /mnt"              //����
#define CPAWE_CMD "cp /mnt/awe4000r ../awe4000rbak"		//����
#define CPSQL_CMD "cp /mnt/libawe.sql ../libawe.sql"	//����
#define RMAWE_CMD "rm -f ../awe4000r"                   //ɾ��
#define MVAWE_CMD "mv ../awe4000rbak ../awe4000r"       //������
#define UMOUNT_CMD "umount /mnt"                      //�����

#endif