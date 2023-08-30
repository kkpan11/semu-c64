# Measuring boot times

I have patched `kernalemu` to provide me with 6502 CPU INSN and cycle
counts during boot. Here is what to expect when you run release
v0.0.2. The two figures at the start of each line are the timings for
the respective *previous* line, in terms of INSNs and cycles (from the
`fake6502` emulator underlying `kernalemu`):

```
C-64 SEMU RISC-V EMULATOR
[        2163         6374]     gIT COMMIT: $iD: 3DC721505BDB572B69C70BAB73B62C895D59FB7C $
[        2637         7797]     EMU STATE BEGIN: 86a6, SIZE: 002A
[        6736        19433]     VM STATE BEGIN: 85c8, SIZE: 00C3
[       10863        31146]     [    0.000000] Linux version 6.1.49 (ok@ryzen) (riscv32-buildroot-linux-gnu-gcc.br_real (Buildroot 2023.05.1) 12.3.0, GNU ld (GNU Binutils) 2.39) #1 Mon Aug 28 21:35:13 CEST 2023
[   308119249    937013361]     [    0.000000] Machine model: semu
[   310076614    942970684]     [    0.000000] earlycon: ns16550 at MMIO 0xf4000000 (options '')
[   313056617    952045088]     [    0.000000] printk: bootconsole [ns16550] enabled
[   317463477    965449118]     [    0.000000] Zone ranges:
[   500494555   1523601187]     [    0.000000]   Normal   [mem 0x0000000000000000-0x0000000000bfffff]
[   506723872   1542547329]     [    0.000000] Movable zone start for each node
[   510134869   1552923070]     [    0.000000] Early memory node ranges
[   513226893   1562327771]     [    0.000000]   node   0: [mem 0x0000000000000000-0x0000000000bfffff]
[   518686116   1578931662]     [    0.000000] Initmem setup node 0 [mem 0x0000000000000000-0x0000000000bfffff]
[   524437533   1596420701]     [    0.000000] SBI specification v0.3 detected
[   615260388   1871503665]     [    0.000000] SBI implementation ID=0x999 Version=0x1
[   619686958   1884965960]     [    0.000000] SBI TIME extension detected
[   622958304   1894917918]     [    0.000000] SBI SRST extension detected
[   626263105   1904971091]     [    0.000000] riscv: base ISA extensions aim
[   632514919   1923990035]     [    0.000000] riscv: ELF capabilities aim
[   636070976   1934805850]     [    0.000000] Built 1 zonelists, mobility grouping off.  Total pages: 3048
[   667308177   2029672815]     [    0.000000] Kernel command line: earlycon console=ttyS0 rootfstype=cramfs root=mtd0 phram.phram=mtd0,0x0c00000,0x400000
[   674113494   2050376039]     [    0.000000] Dentry cache hash table entries: 2048 (order: 1, 8192 bytes, linear)
[   707788591   2152743047]     [    0.000000] Inode-cache hash table entries: 1024 (order: 0, 4096 bytes, linear)
[   715481086   2176129529]     [    0.000000] mem auto-init: stack:off, heap alloc:off, heap free:off
[   720679889   2191947335]     [    0.000000] Memory: 7304K/12288K available (3296K kernel code, 336K rwdata, 861K rodata, 159K init, 168K bss, 4984K reserved, 0K cma-reserved)
[   765920970   2328731289]     [    0.000000] SLUB: HWalign=64, Order=0-3, MinObjects=0, CPUs=1, Nodes=1
[   808979663   2459501377]     [    0.000000] NR_IRQS: 64, nr_irqs: 64, preallocated irqs: 0
[   839443737   2552057319]     [    0.000000] riscv-intc: 32 local interrupts mapped
[   856182147   2602978194]     [    0.000000] plic: interrupt-controller@0: mapped 31 interrupts with 1 handlers for 1 contexts.
[   959303980   2913966499]     [    0.000000] riscv-timer: riscv_timer_init_dt: Registering clocksource cpuid [0] hartid [0]
[   972625781   2954493547]     [    0.000000] clocksource: riscv_clocksource: mask: 0xffffffffffffffff max_cycles: 0xefdb196da, max_idle_ns: 440795204367 ns
[   985228669   2992822956]     [    0.000006] sched_clock: 64 bits at 65MHz, resolution 15ns, wraps every 2199023255550ns
[   996053710   3025739301]     [    0.001222] Console: colour dummy device 80x25
[  1027528875   3121713752]     [    0.001489] Calibrating delay loop (skipped), value calculated using timer frequency.. 130.00 BogoMIPS (lpj=650000)
[  1038422333   3154876866]     [    0.001793] pid_max: default: 32768 minimum: 301
[  1042711182   3167933048]     [    0.002981] Mount-cache hash table entries: 1024 (order: 0, 4096 bytes, linear)
[  1075976661   3269161859]     [    0.003247] Mountpoint-cache hash table entries: 1024 (order: 0, 4096 bytes, linear)
[  1083439510   3291877850]     [    0.008485] ASID allocator disabled (0 bits)
[  1227056928   3729316343]     [    0.010509] devtmpfs: initialized
[  1281963224   3896566877]     [    0.016576] clocksource: jiffies: mask: 0xffffffff max_cycles: 0xffffffff, max_idle_ns: 19112604462750000 ns
[  1460533193   4441386705]     [    0.016877] futex hash table entries: 256 (order: -1, 3072 bytes, linear)
[  1467212372   4461722771]     [    0.026316] NET: Registered PF_NETLINK/PF_ROUTE protocol family
[  1693950120   5152197777]     [    0.057511] clocksource: Switched to clocksource riscv_clocksource
[  2595257873   7902064614]     [    0.116797] NET: Registered PF_INET protocol family
[  4206335359  12812861918]     [    0.118803] IP idents hash table entries: 2048 (order: 2, 16384 bytes, linear)
[  4259090315  12973488131]     [    0.126628] tcp_listen_portaddr_hash hash table entries: 1024 (order: 0, 4096 bytes, linear)
[  4460554898  13589261109]     [    0.127063] Table-perturb hash table entries: 65536 (order: 6, 262144 bytes, linear)
[  4471469986  13622445171]     [    0.127350] TCP established hash table entries: 1024 (order: 0, 4096 bytes, linear)
[  4480992280  13651430671]     [    0.127801] TCP bind hash table entries: 1024 (order: 1, 8192 bytes, linear)
[  4490929304  13681665551]     [    0.128202] TCP: Hash tables configured (established 1024 bind 1024)
[  4501562246  13714068668]     [    0.128700] UDP hash table entries: 256 (order: 0, 4096 bytes, linear)
[  4516752063  13760342473]     [    0.129017] UDP-Lite hash table entries: 256 (order: 0, 4096 bytes, linear)
[  4525493550  13786944670]     [    0.130168] NET: Registered PF_UNIX/PF_LOCAL protocol family
[  4554014463  13873779566]     [    0.134920] workingset: timestamp_bits=30 max_order=11 bucket_order=0
[  4691360730  14292549786]     [    0.542897] Serial: 8250/16550 driver, 4 ports, IRQ sharing disabled
[ 15854471987  48327993843]     [    0.551164] printk: console [ttyS0] disabled
[ 16088472174  49041516957]     [    0.551466] f4000000.serial: ttyS0 at MMIO 0xf4000000 (irq = 1, base_baud = 312500) is a 16550
[ 16099820106  49076050244]     [    0.551812] printk: console [ttyS0] enabled
[ 16107798178  49100349808]     [    0.551812] printk: console [ttyS0] enabled
[ 16110291560  49107954778]     [    0.552110] printk: bootconsole [ns16550] disabled
[ 16116764036  49127673732]     [    0.552110] printk: bootconsole [ns16550] disabled
[ 16119495876  49136005967]     [    0.559418] phram: mtd0 device: 0x400000 at 0xc00000 for erasesize 0x1000
[ 16326463290  49767066870]     [    0.566120] cramfs: checking physical address 0x00000000 for linear cramfs image
[ 16514952166  50341294365]     [    0.566405] cramfs: linear cramfs image on mtd:mtd0 appears to be 3260 KB in size
[ 16523501654  50367344849]     [    0.566854] VFS: Mounted root (cramfs filesystem) readonly on device 31:0.
[ 16536442679  50406787709]     [    0.567317] devtmpfs: mounted
[ 16545440495  50434234629]     [    0.568472] Freeing unused kernel image (initmem) memory: 156K
[ 16582997299  50548673097]     [    0.568722] Kernel memory protection not selected by kernel config.
[ 16589886400  50569670084]     [    0.569018] Run /sbin/init as init process
[ 16596769491  50590653983]     Starting syslogd: OK
[ 25451779402  77619840314]     Starting klogd: OK
[ 27151136247  82808624155]     Running sysctl: OK
[ 32470315218  99044736342]     Starting network: OK
[ 38076669271 116164194512]
[ 41727918869 127302363903]     Welcome to Buildroot
[ 41758779219 127396453645]     buildroot login: root
[ 43605964984 133030343892]     # pwd
[ 46426246175 141637349795]     /root
[ 46441150281 141682834802]     #
```

If you press any key during boot, timing might vary slightly due to
the input handling. You need to divide the second figure by about a
million to get real time in seconds on a C-64. The last part was done
manually, of course, so your mileage *will* vary.

I still need to clean up and upload my patched `kernalemu`, as that
allows to boot to this stage in 8.5min on an AMD Ryzen PC.
