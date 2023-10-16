# Create hd for QEMU:

dd if=/dev/zero of=fat.img bs=1k count=1440
mformat -i fat.img -f 1440 ::
mmd -i fat.img ::/EFI
mmd -i fat.img ::/EFI/BOOT
mcopy -i fat.img helloworld.efi ::/EFI/BOOT
mkgpt -o hdimage.bin --image-size 4096 --part fat.img --type system

qemu-system-x86_64 -L ./ -pflash /usr/share/qemu/OVMF.fd -hda hdimage.bin -net none -nographic
