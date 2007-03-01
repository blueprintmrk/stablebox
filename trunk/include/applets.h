/*
 * applets.h - a listing of all busybox applets.
 *
 * If you write a new applet, you need to add an entry to this list to make
 * busybox aware of it.
 *
 * It is CRUCIAL that this listing be kept in ascii order, otherwise the binary
 * search lookup contributed by Gaute B Strokkenes stops working. If you value
 * your kneecaps, you'll be sure to *make sure* that any changes made to this
 * file result in the listing remaining in ascii order. You have been warned.
 */

#undef APPLET
#undef APPLET_ODDNAME
#undef APPLET_NOUSAGE


#if defined(PROTOTYPES)
# define APPLET(a,b,c) extern int a##_main(int argc, char **argv);
# define APPLET_NOUSAGE(a,b,c,d) extern int b##_main(int argc, char **argv);
# define APPLET_ODDNAME(a,b,c,d,e) extern int b##_main(int argc, char **argv);
#elif defined(MAKE_USAGE)
# ifdef CONFIG_FEATURE_VERBOSE_USAGE
#  define APPLET(a,b,c) a##_trivial_usage "\n\n" a##_full_usage "\0"
#  define APPLET_NOUSAGE(a,b,c,d) "\b\0"
#  define APPLET_ODDNAME(a,b,c,d,e) e##_trivial_usage "\n\n" e##_full_usage "\0"
# else
#  define APPLET(a,b,c) a##_trivial_usage "\0"
#  define APPLET_NOUSAGE(a,b,c,d) "\b\0"
#  define APPLET_ODDNAME(a,b,c,d,e) e##_trivial_usage "\0"
# endif
#elif defined(MAKE_LINKS)
# define APPLET(a,b,c) LINK b a
# define APPLET_NOUSAGE(a,b,c,d) LINK c a
# define APPLET_ODDNAME(a,b,c,d,e) LINK c a
#else
  const struct BB_applet applets[] = {
# define APPLET(a,b,c) {#a,a##_main,b,c},
# define APPLET_NOUSAGE(a,b,c,d) {#a,b##_main,c,d},
# define APPLET_ODDNAME(a,b,c,d,e) {#a,b##_main,c,d},
#endif

#ifdef CONFIG_INSTALL_NO_USR
# define _BB_DIR_USR_BIN _BB_DIR_BIN
# define _BB_DIR_USR_SBIN _BB_DIR_SBIN
#endif


USE_TEST(APPLET_NOUSAGE([, test, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_TEST(APPLET_NOUSAGE([[, test, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_ADDGROUP(APPLET(addgroup, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_ADDUSER(APPLET(adduser, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_ADJTIMEX(APPLET(adjtimex, _BB_DIR_SBIN, _BB_SUID_NEVER))
USE_AR(APPLET(ar, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_ARPING(APPLET(arping, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_ASH(APPLET_NOUSAGE(ash, ash, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_AWK(APPLET(awk, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_BASENAME(APPLET(basename, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_BBCONFIG(APPLET(bbconfig, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_BUNZIP2(APPLET(bunzip2, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
/* Always enabled. */
APPLET_NOUSAGE(busybox, busybox, _BB_DIR_BIN, _BB_SUID_MAYBE)
USE_BUNZIP2(APPLET_ODDNAME(bzcat, bunzip2, _BB_DIR_USR_BIN, _BB_SUID_NEVER, bzcat))
USE_CAL(APPLET(cal, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_CAT(APPLET(cat, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_CATV(APPLET(catv, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_CHATTR(APPLET(chattr, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_CHGRP(APPLET(chgrp, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_CHMOD(APPLET(chmod, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_CHOWN(APPLET(chown, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_CHROOT(APPLET(chroot, _BB_DIR_USR_SBIN, _BB_SUID_NEVER))
USE_CHVT(APPLET(chvt, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_CKSUM(APPLET(cksum, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_CLEAR(APPLET(clear, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_CMP(APPLET(cmp, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_COMM(APPLET(comm, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_CP(APPLET(cp, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_CPIO(APPLET(cpio, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_CROND(APPLET(crond, _BB_DIR_USR_SBIN, _BB_SUID_NEVER))
USE_CRONTAB(APPLET(crontab, _BB_DIR_USR_BIN, _BB_SUID_ALWAYS))
USE_CUT(APPLET(cut, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_DATE(APPLET(date, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_DC(APPLET(dc, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_DD(APPLET(dd, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_DEALLOCVT(APPLET(deallocvt, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_DELGROUP(APPLET_ODDNAME(delgroup, deluser, _BB_DIR_BIN, _BB_SUID_NEVER, delgroup))
USE_DELUSER(APPLET(deluser, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_DEVFSD(APPLET(devfsd, _BB_DIR_SBIN, _BB_SUID_NEVER))
USE_DF(APPLET(df, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_DIFF(APPLET(diff, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_DIRNAME(APPLET(dirname, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_DMESG(APPLET(dmesg, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_DNSD(APPLET(dnsd, _BB_DIR_USR_SBIN, _BB_SUID_ALWAYS))
USE_DOS2UNIX(APPLET(dos2unix, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_DPKG(APPLET(dpkg, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_DPKG_DEB(APPLET_ODDNAME(dpkg-deb, dpkg_deb, _BB_DIR_USR_BIN, _BB_SUID_NEVER, dpkg_deb))
USE_DU(APPLET(du, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_DUMPKMAP(APPLET(dumpkmap, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_APP_DUMPLEASES(APPLET(dumpleases, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_E2FSCK(APPLET(e2fsck, _BB_DIR_SBIN, _BB_SUID_NEVER))
USE_E2LABEL(APPLET_NOUSAGE(e2label, tune2fs, _BB_DIR_SBIN, _BB_SUID_NEVER))
USE_ECHO(APPLET(echo, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_ED(APPLET(ed, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_FEATURE_GREP_EGREP_ALIAS(APPLET_NOUSAGE(egrep, grep, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_EJECT(APPLET(eject, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_ENV(APPLET(env, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_ETHER_WAKE(APPLET_ODDNAME(ether-wake, etherwake, _BB_DIR_USR_BIN, _BB_SUID_NEVER, ether_wake))
USE_EXPR(APPLET(expr, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_FAKEIDENTD(APPLET(fakeidentd, _BB_DIR_USR_SBIN, _BB_SUID_NEVER))
USE_FALSE(APPLET(false, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_FBSET(APPLET(fbset, _BB_DIR_USR_SBIN, _BB_SUID_NEVER))
USE_FDFLUSH(APPLET_ODDNAME(fdflush, freeramdisk, _BB_DIR_BIN, _BB_SUID_NEVER, fdflush))
USE_FDFORMAT(APPLET(fdformat, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_FDISK(APPLET(fdisk, _BB_DIR_SBIN, _BB_SUID_NEVER))
USE_FEATURE_GREP_FGREP_ALIAS(APPLET_NOUSAGE(fgrep, grep, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_FIND(APPLET(find, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_FINDFS(APPLET(findfs, _BB_DIR_USR_SBIN, _BB_SUID_NEVER))
USE_FOLD(APPLET(fold, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_FREE(APPLET(free, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_FREERAMDISK(APPLET(freeramdisk, _BB_DIR_SBIN, _BB_SUID_NEVER))
USE_FSCK(APPLET(fsck, _BB_DIR_SBIN, _BB_SUID_NEVER))
USE_E2FSCK(APPLET_NOUSAGE(fsck.ext2, e2fsck, _BB_DIR_SBIN, _BB_SUID_NEVER))
USE_E2FSCK(APPLET_NOUSAGE(fsck.ext3, e2fsck, _BB_DIR_SBIN, _BB_SUID_NEVER))
USE_FSCK_MINIX(APPLET_ODDNAME(fsck.minix, fsck_minix, _BB_DIR_SBIN, _BB_SUID_NEVER, fsck_minix))
USE_FTPGET(APPLET_ODDNAME(ftpget, ftpgetput, _BB_DIR_USR_BIN, _BB_SUID_NEVER,ftpget))
USE_FTPPUT(APPLET_ODDNAME(ftpput, ftpgetput, _BB_DIR_USR_BIN, _BB_SUID_NEVER,ftpput))
USE_FUSER(APPLET(fuser, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_GETOPT(APPLET(getopt, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_GETTY(APPLET(getty, _BB_DIR_SBIN, _BB_SUID_NEVER))
USE_GREP(APPLET(grep, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_GUNZIP(APPLET(gunzip, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_GZIP(APPLET(gzip, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_HALT(APPLET(halt, _BB_DIR_SBIN, _BB_SUID_NEVER))
USE_HDPARM(APPLET(hdparm, _BB_DIR_SBIN, _BB_SUID_NEVER))
USE_HEAD(APPLET(head, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_HEXDUMP(APPLET(hexdump, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_HOSTID(APPLET(hostid, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_HOSTNAME(APPLET(hostname, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_HTTPD(APPLET(httpd, _BB_DIR_USR_SBIN, _BB_SUID_NEVER))
USE_HUSH(APPLET_NOUSAGE(hush, hush, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_HWCLOCK(APPLET(hwclock, _BB_DIR_SBIN, _BB_SUID_NEVER))
USE_ID(APPLET(id, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_IFCONFIG(APPLET(ifconfig, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_IFUPDOWN(APPLET_ODDNAME(ifdown, ifupdown, _BB_DIR_SBIN, _BB_SUID_NEVER, ifdown))
USE_IFUPDOWN(APPLET_ODDNAME(ifup, ifupdown, _BB_DIR_SBIN, _BB_SUID_NEVER, ifup))
USE_INETD(APPLET(inetd, _BB_DIR_USR_SBIN, _BB_SUID_NEVER))
USE_INIT(APPLET(init, _BB_DIR_SBIN, _BB_SUID_NEVER))
USE_INSMOD(APPLET(insmod, _BB_DIR_SBIN, _BB_SUID_NEVER))
USE_INSTALL(APPLET(install, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_IP(APPLET(ip, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_IPADDR(APPLET(ipaddr, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_IPCALC(APPLET(ipcalc, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_IPCRM(APPLET(ipcrm, _BB_DIR_USR_BIN, _BB_SUID_ALWAYS))
USE_IPCS(APPLET(ipcs, _BB_DIR_USR_BIN, _BB_SUID_ALWAYS))
USE_IPLINK(APPLET(iplink, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_IPROUTE(APPLET(iproute, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_IPTUNNEL(APPLET(iptunnel, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_KILL(APPLET(kill, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_KILLALL(APPLET_ODDNAME(killall, kill, _BB_DIR_USR_BIN, _BB_SUID_NEVER, killall))
USE_KLOGD(APPLET(klogd, _BB_DIR_SBIN, _BB_SUID_NEVER))
USE_LASH(APPLET(lash, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_LAST(APPLET(last, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_LENGTH(APPLET(length, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_LESS(APPLET(less, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_SETARCH(APPLET_NOUSAGE(linux32, setarch, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_SETARCH(APPLET_NOUSAGE(linux64, setarch, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_FEATURE_INITRD(APPLET_NOUSAGE(linuxrc, init, _BB_DIR_ROOT, _BB_SUID_NEVER))
USE_LN(APPLET(ln, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_LOADFONT(APPLET(loadfont, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_LOADKMAP(APPLET(loadkmap, _BB_DIR_SBIN, _BB_SUID_NEVER))
USE_LOGGER(APPLET(logger, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_LOGIN(APPLET(login, _BB_DIR_BIN, _BB_SUID_ALWAYS))
USE_LOGNAME(APPLET(logname, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_LOGREAD(APPLET(logread, _BB_DIR_SBIN, _BB_SUID_NEVER))
USE_LOSETUP(APPLET(losetup, _BB_DIR_SBIN, _BB_SUID_NEVER))
USE_LS(APPLET(ls, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_LSATTR(APPLET(lsattr, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_LSMOD(APPLET(lsmod, _BB_DIR_SBIN, _BB_SUID_NEVER))
USE_UNLZMA(APPLET_ODDNAME(lzmacat, unlzma, _BB_DIR_USR_BIN, _BB_SUID_NEVER, lzmacat))
USE_MAKEDEVS(APPLET(makedevs, _BB_DIR_SBIN, _BB_SUID_NEVER))
USE_MD5SUM(APPLET(md5sum, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_MDEV(APPLET(mdev, _BB_DIR_SBIN, _BB_SUID_NEVER))
USE_MESG(APPLET(mesg, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_MKDIR(APPLET(mkdir, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_MKE2FS(APPLET(mke2fs, _BB_DIR_SBIN, _BB_SUID_NEVER))
USE_MKFIFO(APPLET(mkfifo, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_MKE2FS(APPLET_NOUSAGE(mkfs.ext2, mke2fs, _BB_DIR_SBIN, _BB_SUID_NEVER))
USE_MKE2FS(APPLET_NOUSAGE(mkfs.ext3, mke2fs, _BB_DIR_SBIN, _BB_SUID_NEVER))
USE_MKFS_MINIX(APPLET_ODDNAME(mkfs.minix, mkfs_minix, _BB_DIR_SBIN, _BB_SUID_NEVER, mkfs_minix))
USE_MKNOD(APPLET(mknod, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_MKSWAP(APPLET(mkswap, _BB_DIR_SBIN, _BB_SUID_NEVER))
USE_MKTEMP(APPLET(mktemp, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_MODPROBE(APPLET(modprobe, _BB_DIR_SBIN, _BB_SUID_NEVER))
USE_MORE(APPLET(more, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_MOUNT(APPLET(mount, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_MOUNTPOINT(APPLET(mountpoint, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_MSH(APPLET_NOUSAGE(msh, msh, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_MT(APPLET(mt, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_MV(APPLET(mv, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_NAMEIF(APPLET(nameif, _BB_DIR_SBIN, _BB_SUID_NEVER))
USE_NC(APPLET(nc, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_NETSTAT(APPLET(netstat, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_NICE(APPLET(nice, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_NOHUP(APPLET(nohup, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_NSLOOKUP(APPLET(nslookup, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_OD(APPLET(od, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_OPENVT(APPLET(openvt, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_PASSWD(APPLET(passwd, _BB_DIR_USR_SBIN, _BB_SUID_NEVER))
USE_PATCH(APPLET(patch, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_PIDOF(APPLET(pidof, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_PING(APPLET(ping, _BB_DIR_BIN, _BB_SUID_MAYBE))
USE_PING6(APPLET(ping6, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_PIPE_PROGRESS(APPLET_NOUSAGE(pipe_progress, pipe_progress, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_PIVOT_ROOT(APPLET(pivot_root, _BB_DIR_SBIN, _BB_SUID_NEVER))
USE_HALT(APPLET_ODDNAME(poweroff, halt, _BB_DIR_SBIN, _BB_SUID_NEVER, poweroff))
USE_PRINTENV(APPLET(printenv, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_PRINTF(APPLET(printf, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_PS(APPLET(ps, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_PWD(APPLET(pwd, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_RDATE(APPLET(rdate, _BB_DIR_USR_SBIN, _BB_SUID_NEVER))
USE_READLINK(APPLET(readlink, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_READPROFILE(APPLET(readprofile, _BB_DIR_USR_SBIN, _BB_SUID_NEVER))
USE_REALPATH(APPLET(realpath, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_HALT(APPLET_ODDNAME(reboot, halt, _BB_DIR_SBIN, _BB_SUID_NEVER, reboot))
USE_RENICE(APPLET(renice, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_RESET(APPLET(reset, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_RM(APPLET(rm, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_RMDIR(APPLET(rmdir, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_RMMOD(APPLET(rmmod, _BB_DIR_SBIN, _BB_SUID_NEVER))
USE_ROUTE(APPLET(route, _BB_DIR_SBIN, _BB_SUID_NEVER))
USE_RPM(APPLET(rpm, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_RPM2CPIO(APPLET(rpm2cpio, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_RUN_PARTS(APPLET_ODDNAME(run-parts, run_parts, _BB_DIR_BIN, _BB_SUID_NEVER, run_parts))
USE_RUNLEVEL(APPLET(runlevel, _BB_DIR_SBIN, _BB_SUID_NEVER))
USE_RX(APPLET(rx, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_SED(APPLET(sed, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_SEQ(APPLET(seq, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_SETARCH(APPLET(setarch, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_SETCONSOLE(APPLET(setconsole, _BB_DIR_SBIN, _BB_SUID_NEVER))
USE_SETKEYCODES(APPLET(setkeycodes, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_SETLOGCONS(APPLET(setlogcons, _BB_DIR_USR_SBIN, _BB_SUID_NEVER))
USE_SETSID(APPLET(setsid, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_FEATURE_SH_IS_ASH(APPLET_NOUSAGE(sh, ash, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_FEATURE_SH_IS_HUSH(APPLET_NOUSAGE(sh, hush, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_FEATURE_SH_IS_LASH(APPLET_NOUSAGE(sh, lash, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_FEATURE_SH_IS_MSH(APPLET_NOUSAGE(sh, msh, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_SHA1SUM(APPLET(sha1sum, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_SLEEP(APPLET(sleep, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_SORT(APPLET(sort, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_START_STOP_DAEMON(APPLET_ODDNAME(start-stop-daemon, start_stop_daemon, _BB_DIR_SBIN, _BB_SUID_NEVER, start_stop_daemon))
USE_STAT(APPLET(stat, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_STRINGS(APPLET(strings, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_STTY(APPLET(stty, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_SU(APPLET(su, _BB_DIR_BIN, _BB_SUID_ALWAYS))
USE_SULOGIN(APPLET(sulogin, _BB_DIR_SBIN, _BB_SUID_NEVER))
USE_SUM(APPLET(sum, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_SWAPONOFF(APPLET_ODDNAME(swapoff, swap_on_off, _BB_DIR_SBIN, _BB_SUID_NEVER,swapoff))
USE_SWAPONOFF(APPLET_ODDNAME(swapon, swap_on_off, _BB_DIR_SBIN, _BB_SUID_NEVER, swapon))
USE_SWITCH_ROOT(APPLET(switch_root, _BB_DIR_SBIN, _BB_SUID_NEVER))
USE_SYNC(APPLET(sync, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_BB_SYSCTL(APPLET(sysctl, _BB_DIR_SBIN, _BB_SUID_NEVER))
USE_SYSLOGD(APPLET(syslogd, _BB_DIR_SBIN, _BB_SUID_NEVER))
USE_TAIL(APPLET(tail, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_TAR(APPLET(tar, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_TEE(APPLET(tee, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_TELNET(APPLET(telnet, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_TELNETD(APPLET(telnetd, _BB_DIR_USR_SBIN, _BB_SUID_NEVER))
USE_TEST(APPLET(test, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_TFTP(APPLET(tftp, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_TIME(APPLET(time, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_TOP(APPLET(top, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_TOUCH(APPLET(touch, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_TR(APPLET(tr, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_TRACEROUTE(APPLET(traceroute, _BB_DIR_USR_BIN, _BB_SUID_MAYBE))
USE_TRUE(APPLET(true, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_TTY(APPLET(tty, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_TUNE2FS(APPLET(tune2fs, _BB_DIR_SBIN, _BB_SUID_NEVER))
USE_APP_UDHCPC(APPLET(udhcpc, _BB_DIR_SBIN, _BB_SUID_NEVER))
USE_APP_UDHCPD(APPLET(udhcpd, _BB_DIR_USR_SBIN, _BB_SUID_NEVER))
USE_UMOUNT(APPLET(umount, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_UNAME(APPLET(uname, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_UNCOMPRESS(APPLET(uncompress, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_UNIQ(APPLET(uniq, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_UNIX2DOS(APPLET_ODDNAME(unix2dos, dos2unix, _BB_DIR_USR_BIN, _BB_SUID_NEVER, unix2dos))
USE_UNLZMA(APPLET(unlzma, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_UNZIP(APPLET(unzip, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_UPTIME(APPLET(uptime, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_USLEEP(APPLET(usleep, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_UUDECODE(APPLET(uudecode, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_UUENCODE(APPLET(uuencode, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_VCONFIG(APPLET(vconfig, _BB_DIR_SBIN, _BB_SUID_NEVER))
USE_VI(APPLET(vi, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_VLOCK(APPLET(vlock, _BB_DIR_USR_BIN, _BB_SUID_ALWAYS))
USE_WATCH(APPLET(watch, _BB_DIR_BIN, _BB_SUID_NEVER))
USE_WATCHDOG(APPLET(watchdog, _BB_DIR_SBIN, _BB_SUID_NEVER))
USE_WC(APPLET(wc, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_WGET(APPLET(wget, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_WHICH(APPLET(which, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_WHO(APPLET(who, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_WHOAMI(APPLET(whoami, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_XARGS(APPLET(xargs, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_YES(APPLET(yes, _BB_DIR_USR_BIN, _BB_SUID_NEVER))
USE_GUNZIP(APPLET_ODDNAME(zcat, gunzip, _BB_DIR_BIN, _BB_SUID_NEVER, zcat))
USE_ZCIP(APPLET(zcip, _BB_DIR_SBIN, _BB_SUID_NEVER))

#if !defined(PROTOTYPES) && !defined(MAKE_USAGE)
	{ 0,NULL,0,0 }
};

#endif
