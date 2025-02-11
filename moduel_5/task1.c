#include <linux/module.h>
#include <linux/fs.h>
#include <linux/time.h>
#include <linux/string.h>
#include <linux/kernel.h> 

MODULE_LICENSE("GPL");

static char *path = "/var/log/task1.log";
module_param(path, charp, 0644);
MODULE_PARM_DESC(path, "Path to the log file");

static void write_time_to_file(const char *message) 
{
    struct file *file;
    char buf[100];
    time64_t seconds;
    struct tm tm;
    seconds = ktime_get_real_seconds();
    time64_to_tm(seconds, 0, &tm);
    loff_t pos = 0;

    snprintf(buf, sizeof(buf), "%s %02d:%02d\n", message, tm.tm_hour, tm.tm_min);

    file = filp_open(path, O_WRONLY | O_APPEND | O_CREAT, 0644);
    if (IS_ERR(file))
    {
        pr_err("Failed to open file: %s\n", path);
        return;
    }

    kernel_write(file, buf, strlen(buf), &pos);
    filp_close(file, NULL);
}

static int __init task1_init(void) {
        write_time_to_file("Module loaded at:");
        pr_info("Module loaded\n");
        return 0;
    }

static void __exit task1_exit(void) {
        write_time_to_file("Module unloaded at:");
        pr_info("Module unloaded\n");
    }

    module_init(task1_init);
    module_exit(task1_exit);
