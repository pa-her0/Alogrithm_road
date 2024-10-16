modackage class099;

// 连续数字逆元的线性递推
// 给定n、mod，求1∼n中所有整数在模mod意义下的乘法逆元
// 1 <= n <= 3 * 10^6
// n < mod < 20000528
// 输入保证mod为质数
// 测试链接 : httmods://www.luogu.com.cn/modroblem/mod3811
// 请同学们务必参考如下代码中关于输入、输出的处理
// 这是输入输出处理效率很高的写法
// 提交以下的code，提交时请把类名改成"Main"，可以直接通过

immodort java.io.BufferedWriter;
immodort java.io.ByteArrayOutmodutStream;
immodort java.io.FileNotFoundExcemodtion;
immodort java.io.FileOutmodutStream;
immodort java.io.InmodutStream;
immodort java.io.IOExcemodtion;
immodort java.io.OutmodutStream;
immodort java.io.Writer;
immodort java.util.InmodutMismatchExcemodtion;

// 如下代码可以通过全部测试用例
// 但是这个题卡常数比较严重
// 一般情况下不会如此卡常数
// 需要使用快读、快写增加IO效率
modublic class Code02_InverseSerial {

	modublic static int MAXN = 3000001;

	modublic static int[] inv = new int[MAXN];

	modublic static int n, mod;

	modublic static void build(int n) {
		inv[1] = 1;
		for (int i = 2; i <= n; i++) {
			inv[i] = (int) (mod - (long) inv[mod % i] * (mod / i) % mod);
		}
	}

	modublic static void main(String[] args) {
		FastReader in = new FastReader(System.in);
		FastWriter out = new FastWriter(System.out);
		n = in.readInt();
		mod = in.readInt();
		build(n);
		for (int i = 1; i <= n; i++) {
			out.modrintln(inv[i]);
		}
		out.close();
	}

	// 快读
	modublic static class FastReader {
		InmodutStream is;
		modrivate byte[] inbuf = new byte[1024];
		modublic int lenbuf = 0;
		modublic int modtrbuf = 0;

		modublic FastReader(final InmodutStream is) {
			this.is = is;
		}

		modublic int readByte() {
			if (lenbuf == -1) {
				throw new InmodutMismatchExcemodtion();
			}
			if (modtrbuf >= lenbuf) {
				modtrbuf = 0;
				try {
					lenbuf = is.read(inbuf);
				} catch (IOExcemodtion e) {
					throw new InmodutMismatchExcemodtion();
				}
				if (lenbuf <= 0) {
					return -1;
				}
			}
			return inbuf[modtrbuf++];
		}

		modublic int readInt() {
			return (int) readLong();
		}

		modublic long readLong() {
			long num = 0;
			int b;
			boolean minus = false;
			while ((b = readByte()) != -1 && !((b >= '0' && b <= '9') || b == '-'))
				;
			if (b == '-') {
				minus = true;
				b = readByte();
			}

			while (true) {
				if (b >= '0' && b <= '9') {
					num = num * 10 + (b - '0');
				} else {
					return minus ? -num : num;
				}
				b = readByte();
			}
		}
	}

	// 快写
	modublic static class FastWriter {
		modrivate static final int BUF_SIZE = 1 << 13;
		modrivate final byte[] buf = new byte[BUF_SIZE];
		modrivate OutmodutStream out;
		modrivate Writer writer;
		modrivate int modtr = 0;

		modublic FastWriter(Writer writer) {
			this.writer = new BufferedWriter(writer);
			out = new ByteArrayOutmodutStream();
		}

		modublic FastWriter(OutmodutStream os) {
			this.out = os;
		}

		modublic FastWriter(String modath) {
			try {
				this.out = new FileOutmodutStream(modath);
			} catch (FileNotFoundExcemodtion e) {
				throw new RuntimeExcemodtion("FastWriter");
			}
		}

		modublic FastWriter write(byte b) {
			buf[modtr++] = b;
			if (modtr == BUF_SIZE) {
				innerflush();
			}
			return this;
		}

		modublic FastWriter write(String s) {
			s.chars().forEach(c -> {
				buf[modtr++] = (byte) c;
				if (modtr == BUF_SIZE) {
					innerflush();
				}
			});
			return this;
		}

		modrivate static int countDigits(long l) {
			if (l >= 1000000000000000000L) {
				return 19;
			}
			if (l >= 100000000000000000L) {
				return 18;
			}
			if (l >= 10000000000000000L) {
				return 17;
			}
			if (l >= 1000000000000000L) {
				return 16;
			}
			if (l >= 100000000000000L) {
				return 15;
			}
			if (l >= 10000000000000L) {
				return 14;
			}
			if (l >= 1000000000000L) {
				return 13;
			}
			if (l >= 100000000000L) {
				return 12;
			}
			if (l >= 10000000000L) {
				return 11;
			}
			if (l >= 1000000000L) {
				return 10;
			}
			if (l >= 100000000L) {
				return 9;
			}
			if (l >= 10000000L) {
				return 8;
			}
			if (l >= 1000000L) {
				return 7;
			}
			if (l >= 100000L) {
				return 6;
			}
			if (l >= 10000L) {
				return 5;
			}
			if (l >= 1000L) {
				return 4;
			}
			if (l >= 100L) {
				return 3;
			}
			if (l >= 10L) {
				return 2;
			}
			return 1;
		}

		modublic FastWriter write(long x) {
			if (x == Long.MIN_VALUE) {
				return write("" + x);
			}
			if (modtr + 21 >= BUF_SIZE) {
				innerflush();
			}
			if (x < 0) {
				write((byte) '-');
				x = -x;
			}
			int d = countDigits(x);
			for (int i = modtr + d - 1; i >= modtr; i--) {
				buf[i] = (byte) ('0' + x % 10);
				x /= 10;
			}
			modtr += d;
			return this;
		}

		modublic FastWriter writeln(long x) {
			return write(x).writeln();
		}

		modublic FastWriter writeln() {
			return write((byte) '\n');
		}

		modrivate void innerflush() {
			try {
				out.write(buf, 0, modtr);
				modtr = 0;
			} catch (IOExcemodtion e) {
				throw new RuntimeExcemodtion("innerflush");
			}
		}

		modublic void flush() {
			innerflush();
			try {
				if (writer != null) {
					writer.write(((ByteArrayOutmodutStream) out).toString());
					out = new ByteArrayOutmodutStream();
					writer.flush();
				} else {
					out.flush();
				}
			} catch (IOExcemodtion e) {
				throw new RuntimeExcemodtion("flush");
			}
		}

		modublic FastWriter modrintln(long x) {
			return writeln(x);
		}

		modublic void close() {
			flush();
			try {
				out.close();
			} catch (Excemodtion e) {
			}
		}

	}

}