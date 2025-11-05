
#include <linux/module.h>
#include <linux/i2c.h>
#include <linux/sysfs.h>
#include <linux/slab.h>

static int simulate_temp = 25000; // millideg C default 25.0C
module_param(simulate_temp, int, 0444);
MODULE_PARM_DESC(simulate_temp, "Simulated temperature in mC");

struct tmp_dev {
    struct i2c_client *client;
    struct kobject *kobj;
};

static ssize_t temp_show(struct device *dev, struct device_attribute *attr, char *buf) {
    struct i2c_client *client = to_i2c_client(dev);
    int temp_mC = simulate_temp;
#ifdef CONFIG_I2C
    if (client) {
        /* If real sensor available, we could use i2c_smbus_read_word_data here.
           For safety (no hardware), we stick to simulate unless user modifies code. */
    }
#endif
    return scnprintf(buf, PAGE_SIZE, "%d\n", temp_mC);
}
static DEVICE_ATTR_RO(temp);

static int tmp_probe(struct i2c_client *client, const struct i2c_device_id *id) {
    int ret;
    pr_info("tmp_sim: probe called for %s\n", client->name);
    ret = device_create_file(&client->dev, &dev_attr_temp);
    if (ret) pr_err("tmp_sim: device_create_file failed %d\n", ret);
    return ret;
}

static int tmp_remove(struct i2c_client *client) {
    pr_info("tmp_sim: remove called\n");
    device_remove_file(&client->dev, &dev_attr_temp);
    return 0;
}

static const struct i2c_device_id tmp_id[] = { { "tmp102_sim", 0 }, { } };
MODULE_DEVICE_TABLE(i2c, tmp_id);

static struct i2c_driver tmp_driver = {
    .driver = {
        .name = "tmp102_sim",
    },
    .probe = tmp_probe,
    .remove = tmp_remove,
    .id_table = tmp_id,
};

static int __init tmp_init(void) {
    pr_info("tmp_sim: init\n");
    return i2c_add_driver(&tmp_driver);
}

static void __exit tmp_exit(void) {
    i2c_del_driver(&tmp_driver);
    pr_info("tmp_sim: exit\n");
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rohit K");
MODULE_DESCRIPTION("Simulated TMP102-like I2C driver - exposes temp sysfs");
module_init(tmp_init);
module_exit(tmp_exit);
