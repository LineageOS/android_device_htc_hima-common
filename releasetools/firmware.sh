#!/sbin/sh

set -e

# Mount ADSP firmware partition
mkdir -p /firmware/adsp
mount -t vfat /dev/block/bootdevice/by-name/adsp /firmware/adsp


# Symlink with image directory if its on older fw, or without it if its >= 6.0
if [ -f "/firmware/adsp/image/ADSP.MDT" ]; then
	cd /firmware/adsp/image
	find . -type f | while read file; do ln -s /firmware/adsp/image/$file /system/vendor/firmware/$(echo $file | tr A-Z a-z ) ; done
	echo "Symlinked ADSP android 5.1.1 style";
else
	cd /firmware/adsp
	find . -type f | while read file; do ln -s /firmware/adsp/$file /system/vendor/firmware/$(echo $file | tr A-Z a-z ) ; done
	echo "Symlinked ADSP android 6.0+ style";
fi

cd /
umount /firmware/adsp
exit 0
