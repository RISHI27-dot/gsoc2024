#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <string.h>

#define QUEUE_NAME "/test_queue"
#define MAX_SIZE 10
#define MAX_MSG_SIZE 1024
#define NUM_MSG 3

int pid;

void update_pid()
{
  pid = getpid();
}

int main()
{
  int status1;
  unsigned long long a = 0;
  struct mq_attr attr;
  mqd_t mqd;
  int msg_len;
  char buffer[MAX_MSG_SIZE];
  int i;

  update_pid();

  // +++++++++++ mqueue test ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
  attr.mq_flags = 0;              // Flags: none for now
  attr.mq_maxmsg = 10;            // Maximum number of messages in the queue
  attr.mq_msgsize = MAX_MSG_SIZE; // Maximum message size
  attr.mq_curmsgs = 0;            // Current number of messages in the queue

  // Open a message queue with specified attributes and add NUM_MSG messages to it
  mqd = mq_open(QUEUE_NAME, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR, &attr);
  if (mqd == (mqd_t)-1)
  {
    perror("mq_open");
    exit(1);
  }

  msg_len = strlen(buffer) + 1;

  for (int i = 0; i < NUM_MSG; i++)
  {
    sprintf(buffer, "Message - %d", i);
    if (mq_send(mqd, buffer, msg_len, 0) == -1)
    {
      perror("mq_send");
      exit(1);
    }
  }

  // // Close the message queue
  // if (mq_close(mqd) == -1)
  // {
  //   perror("mq_close");
  //   exit(1);
  // }

  // // Unlink the message queue
  // if (mq_unlink(QUEUE_NAME) == -1) {
  //   perror("mq_unlink");
  //   exit(1);
  // }
  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //

  while (1)
  {
    a++;
    printf("%llu pid = %d \n", a, pid);
    sleep(1);
  }
}
