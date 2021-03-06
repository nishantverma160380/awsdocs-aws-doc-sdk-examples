// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX - License - Identifier: Apache - 2.0 

// snippet-start:[s3.cpp.delete_object.inc]
#include <iostream>
#include <aws/core/Aws.h>
#include <aws/s3/S3Client.h>
#include <aws/s3/model/DeleteObjectRequest.h>
#include <awsdoc/s3/s3_examples.h>
// snippet-end:[s3.cpp.delete_object.inc]

/* ////////////////////////////////////////////////////////////////////////////
 * Purpose: Deletes an object from a bucket in Amazon S3.
 *
 * Prerequisites: The bucket containing the object to be deleted.
 *
 * Inputs:
 * - objectKey: The name of the object to delete.
 * - fromBucket: The name of the bucket to delete the object from.
 * - region: The AWS Region to create the bucket in.
 *
 * Outputs: true if the object was deleted; otherwise, false.
 * ///////////////////////////////////////////////////////////////////////// */

// snippet-start:[s3.cpp.delete_object.code]
bool AwsDoc::S3::DeleteObject(const Aws::String& objectKey, 
    const Aws::String& fromBucket,const Aws::String& region)
{
    Aws::Client::ClientConfiguration config;

    if (!region.empty())
    {
        config.region = region;
    }

    Aws::S3::S3Client s3_client(config);

    Aws::S3::Model::DeleteObjectRequest request;

    request.WithKey(objectKey)
        .WithBucket(fromBucket);

    Aws::S3::Model::DeleteObjectOutcome outcome = 
        s3_client.DeleteObject(request);

    if (!outcome.IsSuccess())
    {
        auto err = outcome.GetError();
        std::cout << "Error: DeleteObject: " <<
            err.GetExceptionName() << ": " << err.GetMessage() << std::endl;

        return false;
    }
    else
    {
        return true;
    }
}

int main()
{
    //TODO: The object_key is the unique identifier for the object in the bucket. In this example set,
    //it is the filename you added in put_object.cpp.
    Aws::String object_key = "my-file.txt";
    //TODO: Change from_bucket to the name of a bucket in your account.
    Aws::String from_bucket = "DOC-EXAMPLE-BUCKET";
    //TODO: Set to the AWS Region in which the bucket was created.
    Aws::String region = "us-east-1";

    Aws::SDKOptions options;
    Aws::InitAPI(options);
    {
        if (AwsDoc::S3::DeleteObject(object_key, from_bucket, region))
        {
            std::cout << "Deleted object " << object_key <<
                " from " << from_bucket << "." << std::endl;
        }
    }
    ShutdownAPI(options);

    return 0;
}
// snippet-end:[s3.cpp.delete_object.code]