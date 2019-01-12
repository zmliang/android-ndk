package test.zml.com.myndk.annotation;

/**
 * Author: zml
 * Date  : 2018/11/26 - 09:31
 **/
public class AnnotationTest {

    @UserCase(id="500",description = "This is a test user case")
    public boolean validatePwd(String pwd){
        return pwd.matches("\\w*\\d\\w*");
    }

    @UserCase(id="250")
    public String encryptPwd(String pwd){
        return new StringBuilder(pwd).reverse().toString();
    }

}
