import core.*;

public class axisMovementAgentTest {
    public static void main(String[] args){
        SerialCommunicator communicator = new SerialCommunicator();
        communicator.autoconnect(20);

        //Loop for backwards and forward movement
//        byte[] forward = {(byte) 255, (byte) 0b00000000, 0, 0, 0, 0, 0, (byte) 255, (byte) 0b00000000};
//        byte[] backward = {(byte) 255, (byte) 0b00000010, 0, 0, 0, 0, 0, (byte) 255, (byte) 0b00000010};
//        byte[] forward = {(byte) 255, (byte) 0b00000010, (byte) 255, (byte) 0b00000000, 0, 0, 0, 0, 0};
//        byte[] backward = {(byte) 255, (byte) 0b00000000, (byte) 255, (byte) 0b00000010, 0, 0, 0, 0, 0};
        byte[] forward = {0, 0, 0, 0, (byte) 50, (byte) 0b00000000};
        byte[] backward = {0, 0, 0, 0, (byte) 50, (byte) 0b00000010};

        System.out.println("Writting data");

        communicator.writeData(forward);

        boolean spin = false;

        while (true) {
            byte[] arr = new byte[1];
            if (communicator.available() > 0) {
                communicator.read(arr);
            }
            if (arr[0] == 5) {
                if (spin) {
                    communicator.writeData(forward);
                } else {
                    communicator.writeData(backward);
                }
                spin = !spin;
            }
        }
    }
}
