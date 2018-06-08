import junit.framework.TestCase;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!



public class UrlValidatorTest extends TestCase {

   public UrlValidatorTest(String testName) {
      super(testName);
   }


   public void testManualTest()
   {
		//You can use this function to implement your manual testing	   
	   
   }
   
   /**************************************************
    * Partition Tests
    * URL = [scheme:][//authority][:port][/path][?query]
    * (https://en.wikipedia.org/wiki/Uniform_Resource_Identifier#Syntax)
    * Each [ ] is a partition. 
    * Thus, there are 5 partition tests to run
    * **************************************************/
   String scheme = "https:";
   String authority = "//www.oregonstate.edu";
   String port = ":80";
   String path = "/about";
   String query = "?id=120";
   
   public void testYourFirstPartition() {
	   System.out.println("\n<-- [Partition Testing] 1. Checking URL part 'SCHEME' -->");
	   // generate url validator
		UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
		 
		String finalUrl="";
		String[] validUrlScheme = {"http:", "ftp:", "http:"}; // these three are the only valid ones
		String[] invalidUrlScheme = {"7ht:", "http::", "http", ":", "132"};

		// invalid scheme
		System.out.println("\nChecking invalid scheme... (Expected Results: 'Invalid indeed!!')");
		for (int i = 0; i < invalidUrlScheme.length; i++) {
			finalUrl = invalidUrlScheme[i] + authority;
			if (!urlVal.isValid(finalUrl)) {
				System.out.println("   " + finalUrl + " --> Invalid indeed!!");
			} else {
				System.out.println("   " + finalUrl + " --> Passed as valid. Potential bug!");
			}
		}
		
		// valid scheme  
		System.out.println("\nChecking valid scheme... (Expected Results: 'Great!')");
		for (int i = 0; i < validUrlScheme.length; i++) {
			finalUrl = validUrlScheme[i] + authority;
			if (urlVal.isValid(finalUrl)) {
				System.out.println("   " + finalUrl + " --> Great!");
			} else {
				System.out.println("    " + finalUrl + " --> Passed as invalid. Potential bug!");
			}
		}
   }
 
   public void testYourSecondPartition() {
	   System.out.println("\n<-- [Partition Testing] 2. Checking URL part 'AUTHORITY' -->");
	   // generate url validator
		UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
		
		String finalUrl="";
		String[] validUrlAuthority = {"//www.google.com", "//www.yahoo.co.jp", "//www.findinfo.co.nz", "//www.abcya.uk", "//nickjr.com", "//0.0.0.0", "//255.255.255.255"};
		String[] invalidUrlAuthority = {"//1.2.3.4213213.2", "//camilia.123", "///www.google.com", "/www.google.com", "www.google.com", "!www.google.com", "//256.256.256.256"};

		// invalid authority
		System.out.println("\nChecking invalid authority... (Expected Results: 'Invalid indeed!!')");
		for (int i = 0; i < invalidUrlAuthority.length; i++) {
			finalUrl = scheme + invalidUrlAuthority[i];
			if (!urlVal.isValid(finalUrl)) {
				System.out.println("   " + finalUrl + " --> Invalid indeed!!");
			} else {
				System.out.println("   " + finalUrl + " --> Passed as valid. Potential bug!");
			}
		}
		
		// valid authority  
		System.out.println("\nChecking valid authority... (Expected Results: 'Great!')");
		for (int i = 0; i < validUrlAuthority.length; i++) {
			finalUrl = scheme + validUrlAuthority[i];
			if (urlVal.isValid(finalUrl)) {
				System.out.println("   " + finalUrl + " --> Great!");
			} else {
				System.out.println("   " + finalUrl + " --> Passed as invalid. Potential bug!");
			}
		}	
   }
   
   public void testYourThirdPartition() {
	// Partition testing on PORT ( values from 0 ~ 65535 only)
	   System.out.println("\n<-- [Partition Testing] 3. Checking URL part 'PORT' -->");
		UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
		
		String finalUrl = "";
		String[] validUrlPort = {":65535", ":0", ":1049"};
		String[] invalidUrlPort = {":-8", ":@!#", "::", "501239", ":helloworld", ":65536"};

		// Causes error on all the valid URLs
		// invalid port
		System.out.println("\nChecking invalid port... (Expected Results: 'Invalid indeed!!')");
		for (int i = 0; i < invalidUrlPort.length; i++) {
			finalUrl = scheme + authority + invalidUrlPort[i];
			if (!urlVal.isValid(finalUrl)) {
				System.out.println("   " + finalUrl + " --> Invalid indeed!!");
			} else {
				System.out.println("   " + finalUrl + " --> Passed as valid. Potential bug!");
			}
		}
		
		// valid port  
		System.out.println("\nChecking valid port...  (Expected Results: 'Great!')");
		for (int i = 0; i < validUrlPort.length; i++) {
			finalUrl = scheme + authority + validUrlPort[i];
			if (urlVal.isValid(finalUrl)) {
				System.out.println("   " + finalUrl + " --> Great!");
			} else {
				System.out.println("   " + finalUrl + " --> Passed as invalid. Potential bug!");
			}
		}	
 }
 
   public void testYourFourthPartition() {
	// Partition testing on PATH
	   System.out.println("\n<-- [Partition Testing] 4. Checking URL part 'PATH' -->");
		UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
		
		String finalUrl = "";
		String[] validUrlPath = {"/about", "/id=1", "/12345"};
		String[] invalidUrlPath = {"about", "//about", "%", ":501239ea"};

		// Causes error on all the valid URLs
		// invalid path
		System.out.println("\nChecking invalid path... (Expected Results: 'Invalid indeed!!')");
		for (int i = 0; i < invalidUrlPath.length; i++) {
			finalUrl = scheme + authority + invalidUrlPath[i];
			if (!urlVal.isValid(finalUrl)) {
				System.out.println("   " + finalUrl + " --> Invalid indeed!!");
			} else {
				System.out.println("   " + finalUrl + " --> Passed as valid. Potential bug!");
			}
		}
		
		// valid path  
		System.out.println("\nChecking valid port...  (Expected Results: 'Great!')");
		for (int i = 0; i < validUrlPath.length; i++) {
			finalUrl = scheme + authority + validUrlPath[i];
			if (urlVal.isValid(finalUrl)) {
				System.out.println("   " + finalUrl + " --> Great!");
			} else {
				System.out.println("   " + finalUrl + " --> Passed as invalid. Potential bug!");
			}
		}	
   }
    
   public void testYourFifthPartition() {
	// Partition testing on QUERY
	   System.out.println("\n<-- [Partition Testing] 5. Checking URL part 'QUERY' -->");
		UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
		
		String finalUrl = "";
		String[] validUrlQuery = {"?class=CS362", "?About", "?q=1;q=2;q=3", "?ServiceLogin?service=mail&passive=true"};
		String[] invalidUrlQuery = {"&action=edit", "//!@$$#$!", "!action=edit"};

		// Causes error on all the valid URLs
		// invalid port
		System.out.println("\nChecking invalid query... (Expected Results: 'Invalid indeed!!')");
		for (int i = 0; i < invalidUrlQuery.length; i++) {
			finalUrl = scheme + authority + invalidUrlQuery[i];
			if (!urlVal.isValid(finalUrl)) {
				System.out.println("   " + finalUrl + " --> Invalid indeed!!");
			} else {
				System.out.println("   " + finalUrl + " --> Passed as valid. Potential bug!");
			}
		}
		
		// valid port  
		System.out.println("\nChecking valid port...  (Expected Results: 'Great!')");
		for (int i = 0; i < validUrlQuery.length; i++) {
			finalUrl = scheme + authority + validUrlQuery[i];
			if (urlVal.isValid(finalUrl)) {
				System.out.println("   " + finalUrl + " --> Great!");
			} else {
				System.out.println("   " + finalUrl + " --> Passed as invalid. Potential bug!");
			}
		}	
   }
   
   public void testYourSixthPartition() {
	// Partition testing on validation routines  
	   System.out.println("\n<-- [Partition Testing] 6. Checking validation routines -->");
	   // should allow double slashes in the path component
		UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_2_SLASHES);
		
		String finalUrl = "";
		String[] validUrlPath = {"/about", "/id=1", "/12345","//about"};
		String[] invalidUrlPath = {"about",  "%", ":501239ea"};

		// Causes error on all the valid URLs
		// invalid path
		System.out.println("\nChecking invalid path... (Expected Results: 'Invalid indeed!!')");
		for (int i = 0; i < invalidUrlPath.length; i++) {
			finalUrl = scheme + authority + invalidUrlPath[i];
			if (!urlVal.isValid(finalUrl)) {
				System.out.println("   " + finalUrl + " --> Invalid indeed!!");
			} else {
				System.out.println("   " + finalUrl + " --> Passed as valid. Potential bug!");
			}
		}
		
		// valid path  
		System.out.println("\nChecking valid port...  (Expected Results: 'Great!')");
		for (int i = 0; i < validUrlPath.length; i++) {
			finalUrl = scheme + authority + validUrlPath[i];
			if (urlVal.isValid(finalUrl)) {
				System.out.println("   " + finalUrl + " --> Great!");
			} else {
				System.out.println("   " + finalUrl + " --> Passed as invalid. Potential bug!");
			}
		}	
 }
   
   //You need to create more test cases for your Partitions if you need to 
   
   
   public void testIsValid()
   {
	   //You can use this function for programming based testing
	   
   }

}
