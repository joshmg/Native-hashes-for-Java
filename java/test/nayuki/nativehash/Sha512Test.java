/* 
 * Native hash functions for Java
 * 
 * Copyright (c) Nayuki Minase
 * http://nayuki.eigenstate.org/page/native-hash-functions-for-java
 */

package nayuki.nativehash;


public final class Sha512Test extends HashTest {
	
	public static void main(String[] args) {
		new Sha512Test().run();
	}
	
	
	protected BlockHasher newHasher(boolean useNative) {
		return useNative ? new Sha512() : new Sha512Java();
	}
	
	
	protected String[][] getTestVectors() {
		return new String[][] {
			{"CF83E1357EEFB8BDF1542850D66D8007D620E4050B5715DC83F4A921D36CE9CE47D0D13C5D85F2B0FF8318D2877EEC2F63B931BD47417A81A538327AF927DA3E", ""},
			{"1F40FC92DA241694750979EE6CF582F2D5D7D28E18335DE05ABC54D0560E0F5302860C652BF08D560252AA5E74210546F369FBBBCE8C12CFC7957B2652FE9A75", "a"},
			{"DDAF35A193617ABACC417349AE20413112E6FA4E89A97EA20A9EEEE64B55D39A2192992A274FC1A836BA3C23A3FEEBBD454D4423643CE80E2A9AC94FA54CA49F", "abc"},
			{"107DBF389D9E9F71A3A95F6C055B9251BC5268C2BE16D6C13492EA45B0199F3309E16455AB1E96118E8A905D5597B72038DDB372A89826046DE66687BB420E7C", "message digest"},
			{"4DBFF86CC2CA1BAE1E16468A05CB9881C97F1753BCE3619034898FAA1AABE429955A1BF8EC483D7421FE3C1646613A59ED5441FB0F321389F77F48A879C7B1F1", "abcdefghijklmnopqrstuvwxyz"},
			{"8E959B75DAE313DA8CF4F72814FC143F8F7779C6EB9F7FA17299AEADB6889018501D289E4900F7E4331B99DEC4B5433AC7D329EEB6DD26545E96E55B874BE909", "abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu"},
		};
	}
	
}
