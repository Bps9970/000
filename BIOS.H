/*  BIOS.H
  * Модуль BIOS.H	 4.02.08.00 52EE5.E8.E8
  * Программист - Помазков М.В.
  * Email - bps9970@gmail.com
  * Дата начала разработки - 18.01.2022 21.31 [ 18.01.2077 ]
  * www.uos.robco.developer	Robco Corp, 2077, All Rights Reserved.
*/

           /* diskinfo_t structure for _bios_disk() */

struct diskinfo_t 
{
    int drive, head, track, sector, nsectors;
    long   buffer;
};

/* cmd values for _bios_disk() */

#define  DISK_RESET     0   /* controller hard reset */
#define  DISK_STATUS    1   /* status of last operation */
#define  DISK_READ      2   /* read sectors */
#define  DISK_WRITE     3   /* write sectors */
#define  DISK_VERIFY    4   /* verify sectors */
#define  DISK_FORMAT    5   /* format track */

int FILE_OPEN_BIOS();
int Bios_Disk(char cmd, int   drive, int head, int track,
    int  sector, int nsects, char buffer);
int Kernel(void);