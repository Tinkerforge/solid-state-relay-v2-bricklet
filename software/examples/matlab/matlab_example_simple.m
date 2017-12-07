function matlab_example_simple()
    import com.tinkerforge.IPConnection;
    import com.tinkerforge.BrickletSolidStateRelayV2;

    HOST = 'localhost';
    PORT = 4223;
    UID = 'XYZ'; % Change XYZ to the UID of your Solid State Relay Bricklet 2.0

    ipcon = IPConnection(); % Create IP connection
    ssr = handle(BrickletSolidStateRelayV2(UID, ipcon), 'CallbackProperties'); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Turn relay on/off 10 times with 1 second delay
    for i = 0:4
        pause(1);
        ssr.setState(true);
        pause(1);
        ssr.setState(false);
    end

    input('Press key to exit\n', 's');
    ipcon.disconnect();
end
