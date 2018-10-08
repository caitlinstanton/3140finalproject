<h1>“Voting Validator”</h1>
<h2>Overview</h2>
Voting, especially in democracies, is a vital part of society but oftentimes not implemented in a
secure and efficient way. The overall function of this project will be to implement a fair and
secret ballot system. Voters will each receive a unique passcode that they must input correctly in
order to be given the option to vote. Once they have correctly inputted their specific passcode,
they can cast their vote, which will not be visible to anyone (other than the vote administrator)
until the entire voting body has cast their votes.
<h2>System Description</h2>
The system will consist of an alphanumeric keypad, a Bluetooth connection (potentially
implemented through an Arduino), an LED display, and a FRDM board. The user flow will be as
follows:
1. Voters will need to “register”. The user will provide some identifying information (i.e.
name, phone number) through the alphanumeric keypad so that we can verify that they
are a unique voter.
2. Once the user is verified as a new voter, a distinct passcode will be sent to them via a
Bluetooth connection to their phone.
3. This code can then be entered on the keypad to “unlock” the voting action for that
specific voter.
a. If an invalid passcode (one that hasn’t been generated yet) is entered, the voter
will not be given access to the voting system and the LED will flash a relevant
message.
b. If a valid passcode (one that has been generated already) is entered, the voter is
considered eligible to vote.
4. The voter will cast their vote by pressing the relevant key on the keypad.
a. While voting, the total votes will not be displayed, so as to not bias the user or
give any indication as to what direction the votes are leaning towards.
5. As soon as the administrative password is entered (the passcode for the first user that is
registered) or the entire voting sample size (the number of registered voters) has cast
their votes, the results of the voting session will be displayed. This ensures that the
results can only be seen by the administrator or once the session is over.
Additional features that can be added if time permits are:
● Creating an administrative account, where the administrator may indicate what the
actual voting options entail (i.e. voting for red or blue) which would be displayed while
the voter is casting their vote
● Making passcodes alphanumeric for more security
● Sending a push notification to the user once their passcode has been inputted correctly to
verify that they are in fact using their own password, and not someone else
<h2>Major Technical Tasks and Testing</h2>
To implement the above algorithm, the major technical tasks we must achieve are:
● Connecting the alphanumeric keypad to the FRDM board by writing code to ensure that
the FRDM board recognizes and processes inputs to the keypad
● Establishing a Bluetooth connection to the user’s specific device so that they can receive
their distinct passcode
● Connecting the LED display so that the updated voting totals will only be displayed after
an administrative passcode has been entered or the entire voting sample size has cast
their vote
The milestones within our system that we will subject to testing will include:
● Ensuring that the voter information is properly verified and that the votes are updated
accordingly, without allowing for multiple votes to be cast by the same voter
● Ensuring that, when registering, a user will put in account information that has never
been inputted before in the system, so no duplicate voters exist
● Ensuring that, when a new voter is registering, they receive a passcode that is distinct
from all previously existing passcodes on their separate devices, and that passcode is the
one that is attributed to their account
● Ensuring that the vote totals will only be displayed if the administrative passcode is
inputted or all voters have voted
● Ensuring that the first account to be registered is considered the admin account, and that
no other accounts have the privileges associated with being an admin
<h2>Development Timeline with Milestones</h2>
During the week starting 28th of March, we plan to purchase all external hardware
components that we need to implement this device. We will start writing pseudocode during this
week as we wait for our hardware to arrive, including the skeleton for voter accounts and voting.
During the next week starting 6th of May, we plan to spend the entire week writing
actual code, incorporating the hardware, and debugging to make our basic functions work.
Finally, during the last week starting on the 13th of May, we plan to try to implement
extra capabilities to make our device more functional and do final debugging and testing.
<h2>Work Distribution Plan</h2>
We plan to work together at all times. Code review and driving will be done by the partner
who is not doing the programming.
<h2>Bill of Materials</h2>
● HC-05 Bluetooth module (BT400_B6)
● SunFounder IIC I2C TWI Serial 2004 20x4 LCD Module Shield
● WIshioT 16 key membrane matrix keyboard keypad
<h2>System Schematic Diagram</h2>
● Bluetooth requires 3.3V, GND, TX and RX plus a CMD (Command) pins for a basic
configuration
● LCD display requires a power and ground pin, as well as data pins
● Keypad requires various PWIM and data pins
