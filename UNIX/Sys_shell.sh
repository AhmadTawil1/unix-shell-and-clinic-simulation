mkdir Loan 
touch Loan/User.txt
mkdir Loan/Request
mkdir Loan/Result
mkdir Loan/Result/Approved
mkdir Loan/Result/Unapproved
touch Criteria.txt
random_number=$((RANDOM % 6 + 5))
echo $random_number > Criteria.txt

cc Main_shell.c -o Main_shell
cc Manager_shell.c -o Manager_shell
cc GetLoan.c -o GetLoan
cc CheckStatus.c -o CheckStatus
cc ApproveLoan.c -o ApproveLoan
cc LoginM.c -o LoginM
cc exit.c -o exit
cc ShowReqNum.c -o ShowReqNum
cc ShowAReqNum.c -o ShowAReqNum
cc ShowUnAReqNum.c -o ShowUnAReqNum
cc CheckRequestList.c -o CheckRequestList
cc ShowReqDetails.c -o ShowReqDetails
cc ShowCriteria.c -o ShowCriteria
cc UpdateCriteria.c -o UpdateCriteria
cc ApproveReqLoan.c -o ApproveReqLoan
cc UnApproveReqLoan.c -o UnApproveReqLoan
cc LogOut.c -o LogOut
./Main_shell