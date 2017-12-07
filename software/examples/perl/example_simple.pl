#!/usr/bin/perl

use Tinkerforge::IPConnection;
use Tinkerforge::BrickletSolidStateRelayV2;

use constant HOST => 'localhost';
use constant PORT => 4223;
use constant UID => 'XYZ'; # Change XYZ to the UID of your Solid State Relay Bricklet 2.0

my $ipcon = Tinkerforge::IPConnection->new(); # Create IP connection
my $ssr = Tinkerforge::BrickletSolidStateRelayV2->new(&UID, $ipcon); # Create device object

$ipcon->connect(&HOST, &PORT); # Connect to brickd
# Don't use device before ipcon is connected

# Turn relay on/off 10 times with 1 second delay
for (my $i = 0; $i < 5; $i++)
{
    sleep(1);
    $ssr->set_state(1);
    sleep(1);
    $ssr->set_state(0);
}

print "Press key to exit\n";
<STDIN>;
$ipcon->disconnect();
